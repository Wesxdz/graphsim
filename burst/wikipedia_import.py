import requests
from bs4 import BeautifulSoup
import re
import wikipediaapi
import argparse

# TODO: Per use config
wiki = wikipediaapi.Wikipedia('GraphLife (youremail.com)', 'en')

# TODO: How to populate default ontology
# particularly how to converge personal and public frames
# Duh use GNN

# Define the URL of the Wikipedia page
# TODO: Consider implications of importing all of Wikipedia vs specific requested page k-hops

parser = argparse.ArgumentParser(
                    prog='Wikipedia Import',
                    description='Generates flecs data from Wikipedia page')
parser.add_argument('url')
args = parser.parse_args()
print(args)
url = args.url

lines = []

def get_page_detail(url):
    # Send an HTTP GET request to fetch the page content
    response = requests.get(url)
    if response.status_code == 200:
        # Parse the HTML content of the page using BeautifulSoup
        soup = BeautifulSoup(response.text, 'html.parser')
        # Extract the title of the Wikipedia page
        page_title = soup.find("h1", {"id": "firstHeading"}).text
        # Clean the page title to make it a valid C struct name
        struct_name = re.sub(r'[^a-zA-Z0-9_]', '_', page_title)

        return page_title, struct_name
    else:
        print("Failed to fetch the Wikipedia page. Check the URL or your internet connection.")
    return None, None

page_title, og_struct_name = get_page_detail(url)
lines.append(f"{og_struct_name} {{")
lines.append(f"    - WikipediaPage {{")
lines.append(f"        - URL{{\"{url}\"}}")
for neighbor in wiki.page(page_title).links.keys():
    struct_name = re.sub(r'[^a-zA-Z0-9_]', '_', neighbor)
    lines.append(f"        - (Hyperlink, {struct_name})")
lines.append("    }")
lines.append("}")

content = "\n".join(lines)
with open(f"../data/{og_struct_name}.flecs", 'w') as f:
    f.write(content)