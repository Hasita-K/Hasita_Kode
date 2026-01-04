import os
import csv
from datetime import datetime
import requests
import matplotlib.pyplot as plt
import schedule
import time
import sqlite3

API_URL = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd&ids=bitcoin&names=Bitcoin&symbols=btc&category=layer-1&price_change_percentage=1h"

PARAMS = {
    'vs_currency': 'usd',
    'order': 'market_cap_desc',
    'per_page': 10,
    'page': 1,
    'sparkline': False
}

DB_NAME = 'crypto.db'

def create_table():
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS crypto_prices (
                   id INTEGER PRIMARY KEY AUTOINCREMENT,
                   timestamp TEXT,
                   coin TEXT,
                   price REAL
                   )
''')
    connection.commit()
    connection.close()

def save_to_database(data):
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()
    timestamp = datetime.now().strftime("%Y-%m-%d %H-%M-%S")
    for coin in data:
        cursor.execute('''
            INSERT INTO crypto_prices (timestamp, coin, price)
                       VALUES (?, ?, ?)
''', (timestamp, coin['id'], coin['current_price']))
    connection.commit()
    connection.close()
    print("Price saved to database")

def search_coin(coin_name):
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()
    cursor.execute('''
        SELECT timestamp, price FROM crypto_prices
                   WHERE coin = ?
                   ORDER By timestamp DESC
                   LIMIT 1
''', (coin_name, ))
    result = cursor.fetchone()
    connection.close()
    #print("RAW RESULT: ", result)
    if result:
        print(f"${result[1]} - {result[0]}")




def fetch_crypto_data():
    response = requests.get(API_URL, params=PARAMS)
    return response.json()




def main():
    create_table()
    print("1. Fetch and store crypto data")
    print("2. Search latest price for a coin")
    
    choice = input("Choose an option: ").strip()

    if choice == "1":
        data = fetch_crypto_data()
        save_to_database(data)
    elif choice == "2":
        coin_name = input("Enter coin name: ").strip().lower()
        search_coin(coin_name)
    else:
        print("Invalid option")    




if __name__ == "__main__":
    main()
