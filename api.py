import sys
import json
import requests

# o token que voce ja possui
token = "a10886a86da2b0e1446cd5c0"

def getMoedasDisponiveis():
    url = f"https://v6.exchangerate-api.com/v6/{token}/codes"

    #Exemplo do Json Retornado:
    # {
	# "result": "success",
	# "documentation": "https://www.exchangerate-api.com/docs",
	# "terms_of_use": "https://www.exchangerate-api.com/terms",
	# "supported_codes": [
	# 	[
	# 		"AED",
	# 		"UAE Dirham"
	# 	],
	# 	[
	# 		"AFN",
	# 		"Afghan Afghani"
	# 	],
	# 	...
    
    try:
        response = requests.get(url)
        dados = response.json()

        #FILTRO JSON:
        # acessa a lista de moedas dentro do json
        for item in dados.get("supported_codes", []):

            codigo = item[0]
            nome = item[1]
            
            # imprime formatado para o c++ 
            print(f"{codigo},{nome}")
            
    except Exception as e:
        # se der erro de conexao nao imprime nada
        pass

def getCambio(moedaBase, moedaCambio):

#     #exemplo json retornado:
#     {
# 	"result": "success",
# 	"documentation": "https://www.exchangerate-api.com/docs",
# 	"terms_of_use": "https://www.exchangerate-api.com/terms",
# 	"time_last_update_unix": 1585267200,
# 	"time_last_update_utc": "Fri, 27 Mar 2020 00:00:00 +0000",
# 	"time_next_update_unix": 1585270800,
# 	"time_next_update_utc": "Sat, 28 Mar 2020 01:00:00 +0000",
# 	"base_code": "EUR",
# 	"target_code": "GBP",
# 	"conversion_rate": 0.8412
# }

    url = f"https://v6.exchangerate-api.com/v6/{token}/pair/{moedaBase}/{moedaCambio}"
    try:
        response = requests.get(url)
        dados = response.json()

        #FILTRO JSON:
        # acessa a lista de moedas dentro do json
        if dados.get("result") == "success":
            taxaCambio = dados.get("conversion_rate")
            print(f"{taxaCambio}")
            
    except Exception as e:
        # se der erro de conexao nao imprime nada
        pass

def getCambioBase(moedaBase):

#     #exemplo json retornado:
#     {
# 	"result": "success",
# 	"documentation": "https://www.exchangerate-api.com/docs",
# 	"terms_of_use": "https://www.exchangerate-api.com/terms",
# 	"time_last_update_unix": 1585267200,
# 	"time_last_update_utc": "Fri, 27 Mar 2020 00:00:00 +0000",
# 	"time_next_update_unix": 1585353700,
# 	"time_next_update_utc": "Sat, 28 Mar 2020 00:00:00 +0000",
# 	"base_code": "USD",
# 	"conversion_rates": {
# 		"USD": 1,
# 		"AUD": 1.4817,
# 		"BGN": 1.7741,
# 		"CAD": 1.3168,
# 		"CHF": 0.9774,
# 		"CNY": 6.9454,
# 		"EGP": 15.7361,
# 		"EUR": 0.9013,
# 		"GBP": 0.7679,
# 		"...": 7.8536,
# 		"...": 1.3127,
# 		"...": 7.4722, etc. etc.
# 	}
# }
    url = f'https://v6.exchangerate-api.com/v6/{token}/latest/{moedaBase}'

    try:
        response = requests.get(url)
        dados = response.json()

        #FILTRO JSON:
        # acessa a lista de moedas dentro do json
        if (dados.get("result") == "success"):
            for codigo, taxa in dados.get("conversion_rates", {}).items():
                print(f"{codigo},{taxa}")
            
    except Exception as e:
        # se der erro de conexao nao imprime nada
        pass



# verifica se o c++ chamou o script passando o argumento correto
if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "getMoedasDisponiveis":
        getMoedasDisponiveis()

    elif len(sys.argv) > 2 and sys.argv[1] == "getCambioBase":
        getCambioBase(sys.argv[2])

    elif len(sys.argv) > 3 and sys.argv[1] == "getCambio":
        getCambio(sys.argv[2], sys.argv[3])