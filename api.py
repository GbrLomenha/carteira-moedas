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

# verifica se o c++ chamou o script passando o argumento correto
if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] == "getMoedasDisponiveis":
        getMoedasDisponiveis()