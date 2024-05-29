from init_agent import init_agent
import numpy as np
import json

def loud_features():
    print("Loud Features")
    
    with open('before_act.json', 'r') as f:
        data = json.load(f)
    
    pixle_map = np.array(data['pixle_map'])
    apple     = np.array(data['apple'])
    haed      = np.array(data['reward'])
    
    return pixle_map, apple, haed


def act():
    try:
        agent = init_agent()
        pixle_map, apple, haed = loud_features()
        map_flat = pixle_map.flatten()
        snake_head_flat = haed.flatten()
        apple_flat = apple.flatten()
        combined_flat = np.concatenate([map_flat, snake_head_flat, apple_flat])
        env = combined_flat.reshape(1, -1)
        action = {
            'action' : agent.act(env)
            }
        with open('action.json', 'w') as f:
            json.dump(action, f, indent=4)
            
    except Exception as e:
        print("act, Something went wrong ", e)
        
act()

