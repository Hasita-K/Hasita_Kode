import json
import os

INPUT_FILE = "nested_data.json"
OUTPUT_FILE = "flattened_data.json"

def flatten_json(data, parent_key = '', sep='.'):
    items = {}

    if isinstance(data, dict):
        for key, value in data.items():
            full_key = f"{parent_key}{sep}{key}" if parent_key else key
            print(full_key)
            items.update(flatten_json(value, full_key, sep=sep))
    elif isinstance(data, list):
        for idx, item in enumerate(data):
            full_key = f"{parent_key}{sep}{idx}" if parent_key else str(idx)
            items.update(flatten_json(item, full_key, sep=sep))

    else:
        items[parent_key] = data
    
    return items

def main():
    if not os.path.exists(INPUT_FILE):
        print("No input file found")
        return
    
    try:
        with open(INPUT_FILE, "r", encoding="utf-8") as f:
            data = json.load(f)
        
        sep = input("Enter your seperator like . or - : ").strip() or '.'

        flattened = flatten_json(data, sep=sep)
        with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
            json.dump(flattened, f, indent = 2)
        print(f"Flattened JSON saved to {OUTPUT_FILE}")
    except Exception as e:
        print("Failed to flatten the data", e)

if __name__ == "__main__":
    main()


