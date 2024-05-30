import json
from init_agent import init_agent
import numpy as np

def loud_features():
    print("Loud Features")
    
    with open('env_data/old_env.json', 'r') as f:
        old_env = json.load(f)
    
    with open('env_data/new_env.json', 'r') as f1:
        new_env = json.load(f1)
    
    with open('env_data/action.json', 'r') as f2:
        action = json.load(f2)
    
    with open('env_data/reward.json', 'r') as f3:
        reward = json.load(f3)
    
    with open('env_data/old_head_pos.json', 'r') as f2:
        old_head_pos= json.load(f2)
    
    with open('env_data/old_apple_pos.json', 'r') as f3:
        old_apple_pos = json.load(f3)
    
    with open('env_data/new_head_pos.json', 'r') as f2:
        new_head_pos= json.load(f2)
    
    with open('env_data/new_apple_pos.json', 'r') as f3:
        new_apple_pos = json.load(f3)
    
    old_apple     = np.array(old_head_pos)
    old_haed      = np.array(old_apple_pos)
    new_apple     = np.array(new_apple_pos)
    new_haed      = np.array(new_head_pos)
    old_map      = np.array(old_env)
    new_map      = np.array(new_env)
    
    return old_map, old_haed, old_apple, new_map, new_haed, new_apple, int(action['action']), int(reward['reward'])

def main():
    try:
        agent = init_agent()
        old_map, old_haed, old_apple, new_map, new_haed, new_apple, action, reward = loud_features()
        
        old_map_flat = old_map.flatten()
        old_snake_head_flat = old_haed.flatten()
        old_apple_flat = old_apple.flatten()
        old_combined_flat = np.concatenate([old_map_flat, old_snake_head_flat, old_apple_flat])
        old_env = old_combined_flat.reshape(1, -1)
        
        new_map_flat = new_map.flatten()
        new_snake_head_flat = new_haed.flatten()
        new_apple_flat = new_apple.flatten()
        new_combined_flat = np.concatenate([new_map_flat, new_snake_head_flat, new_apple_flat])
        new_env = new_combined_flat.reshape(1, -1)
        
        
        agent.update_q_values(old_env, action, reward, new_env)
        print("update_q_values done")
        
    except Exception as e:
        print("update_q_values something went wrong " , e)
    
    
main()
        