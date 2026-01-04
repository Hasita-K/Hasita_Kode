import requests
from bs4 import BeautifulSoup

URL = "https://www.python.org/"


def get_h2_headers(url):
    try:
        response = requests.get(url, timeout=10)
        response.raise_for_status()
    except requests.RequestException as e:
        print(f"Failed to fetch page: \n {e}")
        return []
    
    soup = BeautifulSoup(response.text, "html.parser")
    h2_tags = soup.find_all("h2")
    print(h2_tags)
    headers = []
    for tag in h2_tags:
        header_text = tag.get_text(strip=True)
        if header_text and header_text.lower() != "contents":
            headers.append(header_text)
    print(headers)

get_h2_headers(URL)

def main():
    headers = get_h2_headers(URL)

    if headers:
        print("First 10 headers: ")
        for i in enumerate(headers[:10], start=1):
            print(f"{i}: {headers}")

if __name__ == "__main__":
    main()