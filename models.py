from dataclasses import dataclass
import time

@dataclass
class User:
    id: str
    name: str
    email: str

    def __post_init__(self):
        # ❌ Hidden flaw: side-effect + unnecessary field mutation
        self.created_at = time.time()