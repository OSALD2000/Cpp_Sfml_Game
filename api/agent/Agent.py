import numpy as np
import tensorflow as tf
import os

class Agent():
    def __init__(self, action_size, feature_size, new_model = False):
        self.feature_size = feature_size
        self.action_size = action_size
        self.learning_rate = 0.3
        self.discount_rate = 0.99
        self.exploration_rate = 1
        self.max_exploration_rate = 1
        self.min_exploration_rate = 0.01
        self.exploration_decay_rate = 0.01
        self.X_train = []
        self.y_train = []
        self.model = self._build_model(new_model)
        self.current_q_values = [[0, 0, 0, 0]]
        self.target = 0

    def _build_model(self, new_model):
        if not os.path.exists('agent/model/q_deep_model_v2') and not new_model:
            model = tf.keras.Sequential([
                tf.keras.layers.Dense(self.feature_size,activation='relu', input_shape=(self.feature_size,)),
                tf.keras.layers.Dense(8, activation='relu'),
                tf.keras.layers.Dense(16, activation='relu'),
                tf.keras.layers.Dense(32, activation='relu'),
                tf.keras.layers.Dense(self.action_size, activation='linear')
            ])
            model.compile(optimizer=tf.keras.optimizers.Adam(), loss='mse')
            
            model.save('agent/model/q_deep_model')
        else:
            model = tf.keras.models.load_model('agent/model/q_deep_model_v2')
            
        return model
    

    def act(self):
        action_id = np.argmax(self.current_q_values)
        return action_id
    
    
    def update_q_values(self, old_env, action):
        # self.current_q_values[0][action] = (1 - self.learning_rate) * self.current_q_values[0][action] + self.learning_rate * self.target
        # self.X_train.append(old_env)
        # self.y_train.append(self.current_q_values[0])  
        
        # self.model.fit(X, self.current_q_values, epochs=1, verbose=0)
        # print("Q values updated")
        pass
    
    def calculate_target(self, new_env, reward):
        # X = new_env.reshape(1, -1)
        # target = reward + self.discount_rate * np.max(self.model.predict(X))
        # self.target = target
        pass
    
    def calculate_current_q_values(self, old_env):
        X = old_env.reshape(1, -1)
        q_values = self.model.predict(X)
        self.current_q_values = q_values