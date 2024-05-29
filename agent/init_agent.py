from Agent import Agent
import json

def init_agent():
    agent = Agent(action_size=4,
                  feature_size=1604, new_model = False)
    
    return agent