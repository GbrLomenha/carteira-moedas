import requests

cotationUrl = "https://brapi.dev/api/v2/currency"

response = requests.request("GET", cotationUrl, headers = {
    "Authorization": "bm8cmpUYVgzJ5QZ4bjL9H7"
})


listCurrencyUrl = "https://brapi.dev/api/v2/currency/available"
response = requests.request("GET", listCurrencyUrl, headers = {
    "Authorization": "bm8cmpUYVgzJ5QZ4bjL9H7"
})