import json
from init_agent import init_agent

def loud_features():
    print("Loud Features")
    
    with open('after_act.json', 'r') as f:
        data = json.load(f)
    
    old_env = data['old_env']
    new_env = data['new_env']
    action = data['action']
    reward = data['reward']
    
    return old_env, new_env, action, reward

def main():
    try:
        agent = init_agent()
        old_env, new_env, action, reward = loud_features()
        agent.update_q_values(old_env, action, reward, new_env)
        print("update_q_values done")
        
    except Exception as e:
        print("update_q_values something went wrong " , e)
    
    
main()
        