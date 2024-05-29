from init_agent import init_agent
import numpy as np
import json

def loud_features():
    print("Loud Features")
    
    with open('env_data/old_env.json', 'r') as f1:
        old_env = json.load(f1)
    
    with open('env_data/old_head_pos.json', 'r') as f2:
        old_head_pos= json.load(f2)
    
    with open('env_data/old_apple_pos.json', 'r') as f3:
        old_apple_pos = json.load(f3)
    
    old_map   = np.array(old_env)
    apple     = np.array(old_head_pos)
    haed      = np.array(old_apple_pos)
    
    return old_map, apple, haed


def act():
    try:
        agent = init_agent()
        pixle_map, apple, haed = loud_features()
        map_flat = pixle_map.flatten()
        snake_head_flat = haed.flatten()
        apple_flat = apple.flatten()
        combined_flat = np.concatenate([map_flat, snake_head_flat, apple_flat])
        env = combined_flat.reshape(1, -1)
        
        print(env.shape)
        
        action_index = agent.act(env)
        
        action = {'action': str(action_index)}
        
        with open('env_data/action.json', 'w') as f:
            json.dump(action, f)
            
    except Exception as e:
        print("act, Something went wrong ", e)
        
act()

