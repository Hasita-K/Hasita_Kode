import os
import shutil

EXTENSION_MAP = {
    "PDFs": [".pdf"],
    "Images": [".png", ".jpeg", ".jpg"],
    "TextFiles": [".txt"]
}

def get_destination_folder(filename):
    ext = os.path.splitext(filename)[1].lower()
    for folder, extensions in EXTENSION_MAP.items():
        if ext in extensions:
            return folder
    return "Others"

def sort_files(folder_path):
    for file in os.listdir(folder_path):
        full_path = os.path.join(folder_path, file)

        if file == "day_1.py":
            continue

        if os.path.isfile(full_path):
            dest_folder = get_destination_folder(file)
            dest_path = os.path.join(folder_path, dest_folder)

            os.makedirs(dest_path, exist_ok=True)

            #move the file
            shutil.move(full_path, os.path.join(dest_path, file))
            print(f"Moved : {file} -> {dest_folder}/")


if __name__ == "__main__":
    folder = input("Enter the folder path or leave blank: ").strip()
    folder = folder or os.getcwd()

    if not os.path.isdir(folder):
        print("Invalid directory")
    else:
        sort_files(folder)
        print("✅ sorting completed")