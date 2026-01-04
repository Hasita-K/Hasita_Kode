import os
import requests
import textwrap
from bs4 import BeautifulSoup
from PIL import Image, ImageDraw, ImageFont

BASE_URL = "https://quotes.toscrape.com/"
OUTPUT_DIR = "quotes"

def fetch_quotes():
    response = requests.get(BASE_URL)
    soup = BeautifulSoup(response.text, "html.parser")
    quotes = soup.select("div.quote")

    quote_data = []

    for q in quotes[:5]:
        text = q.find("span", class_="text").text.strip("“”")
        author = q.find("small", class_="author").text.strip()
        quote_data.append((text, author))

    return quote_data


def create_image(text, author, index):
    width, height = 900, 500

    # BRAT AESTHETIC
    background_color = "#39FF14"   # neon green
    text_color = "#000000"         # black

    image = Image.new("RGB", (width, height), background_color)
    draw = ImageDraw.Draw(image)

    font = ImageFont.load_default()
    author_font = ImageFont.load_default()

    # BRAT STYLE TEXT
    text = text.upper()
    author = author.upper()

    wrapped = textwrap.fill(text, width=40)

    # Center text vertically
    text_height = wrapped.count("\n") * 15
    y_text = (height - text_height) // 2 - 40

    draw.text((60, y_text), wrapped, fill=text_color, font=font)
    draw.text((60, y_text + text_height + 60), f"- {author}", fill=text_color, font=author_font)

    if not os.path.exists(OUTPUT_DIR):
        os.makedirs(OUTPUT_DIR)

    filename = os.path.join(OUTPUT_DIR, f"brat_quote_{index + 1}.png")
    image.save(filename)
    print(f"✅ Saved: {filename}")


def main():
    quotes = fetch_quotes()
    for idx, (text, author) in enumerate(quotes):
        create_image(text, author, idx)


if __name__ == "__main__":
    main()
