from pydantic import BaseModel
from typing import List

class Environment:
    def __init__(self) -> None:
        self.old_env = []
        self.new_env = []
        self.action = -1
        self.reward = 0
        
        
class OldEnvironmentJSON(BaseModel):
        head_pos: List[int]  = []
        apple_pos: List[int]  = []
        old_map: List[List[int]] = [[]]
            
    
    
class NewEnvironmentJSON(BaseModel):
        head_pos: List[int]  = []
        apple_pos: List[int]  = []
        new_map: List[List[int]] = [[]]
        reward: int = 0