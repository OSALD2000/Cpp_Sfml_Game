import json

old_data = ""

with open('data.json') as f:
    old_data = json.load(f)

new_data = ""
with open('tmp.json') as f:
    new_data = json.load(f)

for data in new_data:
    old_data.append(data)

with open('data.json', 'w') as f:
    json.dump(old_data, f)