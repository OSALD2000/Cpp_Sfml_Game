from Agent import Agent
import json

def init_agent():
    with open('agent_data.json', 'r') as f:
        agent_data = json.load(f)
        
    agent = Agent(state_size= int(agent_data['state_size']), action_size=int(agent_data['action_size']),
                  feature_size=int(agent_data['feature_size']), new_model = False)
    
    return agent