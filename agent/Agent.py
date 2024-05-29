import numpy as np
import tensorflow as tf
from collections import deque
import os

class Agent():
    def __init__(self, action_size, feature_size, new_model = False):
        self.feature_size = feature_size
        self.action_size = action_size
        self.learning_rate = 0.1
        self.discount_rate = 0.99
        self.exploration_rate = 1
        self.max_exploration_rate = 1
        self.min_exploration_rate = 0.01
        self.exploration_decay_rate = 0.01
        
        self.model = self._build_model(new_model)

    def _build_model(self, new_model):
        if not os.path.exists('agent/model/q_deep_model') and not new_model:
            model = tf.keras.Sequential([
                tf.keras.layers.Dense(self.feature_size,activation='relu', input_shape=(self.feature_size,)),
                tf.keras.layers.Dense(24, activation='relu'),
                tf.keras.layers.Dense(self.action_size, activation='linear')
            ])
            model.compile(optimizer=tf.keras.optimizers.Adam(), loss='mse')
            
            model.save('agent/model/q_deep_model')
        else:
            model = tf.keras.models.load_model('agent/model/q_deep_model')
            
        return model
    

    def act(self, env):
        action_id = np.argmax(self.model.predict(env))
        return action_id
    
    
    def update_q_values(self, env, action, reward, new_env):
        
        target = reward + self.discount_rate * np.max(self.model.predict(new_env))

        current_q_values = self.model.predict(env)

        current_q_values[0][action] = (1 - self.learning_rate) * current_q_values[0][action] + self.learning_rate * target

        self.model.fit(env, current_q_values, epochs=1, verbose=0)
        