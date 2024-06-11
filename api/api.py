from fastapi import FastAPI
from agent.Agent import Agent
from agent.Environment import Environment, OldEnvironmentJSON, NewEnvironmentJSON
import numpy as np
import threading
from contextlib import asynccontextmanager
import json


# def overwrite_json_file(filename, new_data):
#         existing_data = []
#         try:
#             with open(filename, 'r') as file:
#                 existing_data = json.load(file)
#         except Exception as e:
#             existing_data = []
            
#         with open(filename, 'w') as file:
#             for data in new_data:
#                 if isinstance(data, np.ndarray):
#                     existing_data.append(data.tolist())
#                 else:
#                     existing_data.append(data)
                    
#             json.dump(existing_data, file, indent=4)


agent = Agent(action_size=4,
                feature_size=1604, new_model = False)

envirmunet = Environment()
            
            
@asynccontextmanager
async def lifespan(app: FastAPI):
    yield
    agent.model.save('agent/model/q_deep_model_v2')

app = FastAPI(lifespan= lifespan)


@app.get("/action", status_code=200)
async def get_action():
    action_index = agent.act()
    envirmunet.action = action_index
    action =  {'action': str(action_index)}
    return action

@app.post("/env_before_act", status_code=200)
async def env_before_act(old_env: OldEnvironmentJSON):
    old_map_flat = np.array(old_env.old_map).flatten()
    old_haed = np.array(old_env.head_pos).flatten()
    old_apple = np.array(old_env.apple_pos).flatten()
    old_combined_flat = np.concatenate([old_map_flat, old_haed, old_apple])
    envirmunet.old_env = old_combined_flat
    thread1 = threading.Thread(target=agent.calculate_current_q_values, args=(envirmunet.old_env,))
    thread1.start()
    
@app.post("/env_after_act", status_code=200)
async def env_after_act(new_env: NewEnvironmentJSON):
    new_map_flat = np.array(new_env.new_map).flatten()
    new_haed = np.array(new_env.head_pos).flatten()
    new_apple = np.array(new_env.apple_pos).flatten()
    new_combined_flat = np.concatenate([new_map_flat, new_haed, new_apple])
    envirmunet.new_env = new_combined_flat
    envirmunet.reward = new_env.reward
    envirmunet.action = new_env.action
    thread2 = threading.Thread(target=agent.calculate_target, args=(envirmunet.new_env, envirmunet.reward,))
    thread2.start()

@app.get("/update_q_values", status_code=200)
async def update_q_values():
    agent.update_q_values(envirmunet.old_env, envirmunet.action)
    
 