from fastapi import FastAPI
from agent.Agent import Agent
from agent.Environment import Environment, OldEnvironmentJSON, NewEnvironmentJSON
import numpy as np

app = FastAPI()
agent = Agent(action_size=4,
                feature_size=1604, new_model = False)

envirmunet = Environment()

@app.get("/action")
async def get_action():
    action_index = agent.act(envirmunet.old_env)
    action =  {'action': str(action_index)}
    return action

@app.post("/env_before_act")
async def env_before_act(old_env: OldEnvironmentJSON):
    old_map_flat = np.array(old_env.old_map).flatten()
    old_haed = np.array(old_env.head_pos).flatten()
    old_apple = np.array(old_env.apple_pos).flatten()
    old_combined_flat = np.concatenate([old_map_flat, old_haed, old_apple])
    old_env = old_combined_flat.reshape(1, -1)
    envirmunet.old_env = old_env
    return

@app.post("/env_after_act")
async def env_after_act(new_env: NewEnvironmentJSON):
    new_map_flat = np.array(new_env.new_map).flatten()
    new_haed = np.array(new_env.head_pos).flatten()
    new_apple = np.array(new_env.apple_pos).flatten()
    new_combined_flat = np.concatenate([new_map_flat, new_haed, new_apple])
    new_env_array = new_combined_flat.reshape(1, -1)
    envirmunet.new_env = new_env_array
    envirmunet.reward = new_env.reward
    return


@app.get("/update_q_values")
async def update_q_values():
    agent.update_q_values(old_env=envirmunet.old_env, action=envirmunet.action, reward= envirmunet.reward, new_env=envirmunet.new_env)
    return
 