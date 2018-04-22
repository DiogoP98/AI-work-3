#include <bits/stdc++.h>
#include <readline/history.h>
#include <readline/readline.h>

using namespace std;

void sentence();

int frase_nome(int i);

int frase_nome_p (int i);

int frase_verbal_s (int i);

int frase_verbal_p (int i);

int check_prep (int i);

int check_contracao_s (int j);

int check_contracao_p (int j);

int check_artigo_s (int j);

int check_artigo_p (int j);

int determiner_f(int i);

int determiner_m(int i);

int determiner_p_m(int i);

int determiner_p_f(int i);

int noun_F (int j);

int noun_p_F (int j);

int noun_M (int j);

int noun_p_M(int j);

int prep (int j);

int artigo_f (int j);

int artigo_p_f (int j);

int artigo_m (int j);

int artigo_p_m (int j);

int verb_v (int j);

int verb_ps (int j);

int contracao_m (int j);

int contracao_f (int j);

int contracao_p_m (int j);

int contracao_p_f (int j);

vector<string> x;

set <string> nome_M = {"cacador", "cachorro", "lobo","rio", "mar", "tempo", "sino", "vento", "martelo", "tambor", "tempo","rosto"};
set <string> nome_F = {"cidade","lagrima","mae","menina","noticia", "floresta","porta","vida"};

set <string> nome_p_M = {"cacadores","cachorros","lobos","mares","martelos","tambores","rios","rostos","sinos","ventos"};
set <string> nome_p_F = {"meninas","lagrimas","florestas","maes","vidas","noticias","cidades","portas"};

set <string> verbo_s = {"bate","bateu","corre","correu"};
set <string> verbo_p = {"batem","bateram","batiam","correm","correram","corriam"};

set <string> preposicao = {"com","para"};

set <string> contracao_M = {"no","pelo"};
set <string> contracao_F = {"na","pela"};

set <string> contracao_p_M = {"nos","pelos"};
set <string> contracao_p_F = {"nas","pelas"};

set <string> artigo_F = {"a","A"};
set <string> artigo_M = {"o","O"};

set <string> artigo_p_M = {"os","Os"};
set <string> artigo_p_F = {"as","As"};

void sentence() {
	int i = frase_nome(0);
	if (i<=0) {
		i = frase_nome_p(0);
		if (!(i<=0))
			i = frase_verbal_p(i);
	}
	else if(i<(int)x.size())
		i = frase_verbal_s(i);
	else printf("Erro\n");
	
	if(i!=(int)x.size())
		printf ("Erro\n");
}

int frase_nome(int i) {
	int j = determiner_f(i);
	if (j==-1) {
		j = noun_F(i);
		if (j==-1) {
			j = determiner_m(i);
			if (j==-1){
				j = noun_M(i);
				if (j != -1)
					printf ("sent(noun_prase(noun(%s)),",x[i].c_str());
			}
			else {
				printf ("sent(noun_prase(determiner(%s),",x[i].c_str());
				i=j;
				j = noun_M(j);
				if (j != -1)
					printf ("noun(%s)),",x[i].c_str());
			}
		}
		else
			printf ("sent(noun_prase(noun(%s)),",x[i].c_str());
	}
	else{
		printf ("sent(noun_prase(determiner(%s),",x[i].c_str());
		i=j;
		j = noun_F(j);
		if (j != -1)
			printf ("noun(%s)),",x[i].c_str());
	}
	return j;
}

int frase_nome_p (int i) {
	int j = determiner_p_f(i);
	if (j==-1) {
		j = noun_p_F(i);
		if (j==-1) {
			j = determiner_p_m(i);
			if (j==-1){
				j = noun_p_M(i);
				if (j != -1)
					printf ("sent(noun_prase(noun(%s)),",x[i].c_str());
			}
			else {
				printf ("sent(noun_prase(determiner(%s),",x[i].c_str());
				i=j;
				j = noun_p_M(j);
				if (j != -1)
					printf ("noun(%s)),",x[i].c_str());
			}
		}
		else
			printf ("sent(noun_prase(noun(%s)),",x[i].c_str());
	}
	else {
		printf ("sent(noun_prase(determiner(%s),",x[i].c_str());
		i=j;
		j = noun_p_F(j);
		if (j != -1)
			printf ("noun(%s)),",x[i].c_str());
	}
	return j;
}

int frase_verbal_s (int i) {
	int j = verb_v(i);
	if (j == (int)x.size()) {
		printf ("verbal phrase(verb(%s)))\n",x[i].c_str());
		return j;
	}
	else {
		if (j!=-1) {
			printf ("verbal phrase(verb(%s),", x[i].c_str());
			int i = j;
			j = check_prep (i);
			if (j == -1) {
				j = check_contracao_s(i);
				if (j==-1) {
					check_contracao_p(i);
					if (j == -1) {
						j= check_artigo_s(i);
						if (j==-1)
							j = check_artigo_p (i);
					}
			}
		}
	}
}
	return j;
}

int frase_verbal_p (int i) {	
	int j = verb_ps(i);

	if (j == (int)x.size()){
		printf ("verbal phrase(verb(%s)))\n",x[i].c_str());
		return j;
	}

	else {
		if (j!=-1) {
			printf ("verbal phrase(verb(%s),", x[i].c_str());
			int i = j;
			j = check_prep (i);
			if (j == -1) {
				j = check_contracao_s(i);
				if (j == -1) {
					check_contracao_p(i);
					if (j == -1) {
						j= check_artigo_s(i);
						if (j==-1)
							j = check_artigo_p (i);
					}
			}
		}
	}
}	
	return j;
}

int check_prep (int i) {
	int k = prep (i);
	int j;
	if (k!=-1) {
		printf ("prepostion(%s),",x[i].c_str());
		j = artigo_f (k); 
		if (j==-1) { //se nao for artigo feminino
			j = artigo_m (k);
			if (j == -1) { //se nao for artigo masculino
				j = artigo_p_m (k);
				if (j == -1) { //se nao for artigo plural masculino
					j = artigo_p_f (k);
					if ( j != -1){
						printf ("article(%s),",x[k].c_str());
						i = j;
						j = noun_p_F (j); //verifica se tem nome a seguir
						printf ("noun(%s)))\n",x[i].c_str());
					}
				}
				else{
					printf ("article(%s),",x[k].c_str());
					i = j;
					j = noun_p_M (j); //verifica se tem nome plural masculino a seguir
					printf ("noun(%s)))\n",x[i].c_str());
				}
			}
			else{
				printf ("article(%s),",x[k].c_str());
				i = j;
				j = noun_M (j); //verifica se tem nome masculino
				printf ("noun(%s)))\n",x[i].c_str());
			}
		}
		else{
			printf ("article(%s),",x[k].c_str());
			i = j;
			j = noun_F (j); //verifica se tem nome feminino
			if(j!=-1)
				printf ("noun(%s)))\n",x[i].c_str());
		}
	} 
	else 
		j=k;
	return j;
}

int check_contracao_s (int j) { //contracao no singular
	int i = contracao_m (j);
	if (i == -1) {
		i = contracao_f (j);

		if (i!= -1){
			printf ("contraction(%s),",x[j].c_str());
			j=i;
			i = noun_F (i);
			if(i!=-1)
				printf ("noun(%s)))\n",x[j].c_str());
		}
	}
	else{		
		printf ("contraction(%s),",x[j].c_str());
		j=i;
		i = noun_M (i);
		if(i!=-1)
			printf ("noun(%s)))\n",x[j].c_str());
	}

	return i;
}

int check_contracao_p (int j) { //contracao no plural
	int i = contracao_p_m(j);
	if (i == -1) {
		i = contracao_p_f (j);

		if (i!= -1){
			printf ("contraction(%s),",x[j].c_str());
			j=i;
			i = noun_p_F (i);
			printf ("noun(%s)))\n",x[j].c_str());
		}
	}
	else{
		printf ("contraction(%s),",x[j].c_str());
		j=i;
		i = noun_p_M (i);
		printf ("noun(%s)))\n",x[j].c_str());
	}

	return i;
}

int check_artigo_s (int j) {
	int i = artigo_m (j);
	if (i == -1) {
		i = artigo_f (j);

		if (i!=-1){
			printf ("contraction(%s),",x[j].c_str());
			j=i;
			i = noun_F (i);
			printf ("noun(%s)))\n",x[j].c_str());
		}
	}

	else{
		printf ("article(%s),",x[j].c_str());
		j=i;
		i = noun_M (i);
		printf ("noun(%s)))\n",x[j].c_str());
	}

	return i;
}

int check_artigo_p (int j) {
	int i = artigo_p_m (j);
	if (i == -1) {
		i = artigo_p_f (j);

		if (i!=-1){
			printf ("contraction(%s),",x[j].c_str());
			j=i;
			i = noun_p_F (i);
			printf ("noun(%s)))\n",x[j].c_str());
		}
	}

	else{
		printf ("article(%s),",x[j].c_str());
		j=i;
		i = noun_p_M (i);		
		printf ("noun(%s)))\n",x[j].c_str());
	}

	return i;
}

int determiner_f(int i) {
	if (artigo_F.find(x[i])!=artigo_F.end())
		return i+1;
	else
		return -1;	
}

int determiner_m(int i) {
	if (artigo_M.find(x[i])!=artigo_M.end())
		return i+1;
	else
		return -1;	
}

int determiner_p_m(int i) {
	if (artigo_p_M.find(x[i])!=artigo_p_M.end())
		return i+1;
	else
		return -1;	
}

int determiner_p_f(int i) {
	if (artigo_p_F.find(x[i])!=artigo_p_F.end())
		return i+1;
	else
		return -1;	
}

int noun_F (int j) {
	if (nome_F.find(x[j])!=nome_F.end())
		return j+1;
	else
		return -1;

}

int noun_p_F (int j) {
	if (nome_p_F.find(x[j])!=nome_p_F.end())
		return j+1;
	else
		return -1;

}

int noun_M (int j) {
	if (nome_M.find(x[j])!=nome_M.end())
		return j+1;
	else
		return -1;

}

int noun_p_M(int j) {
	if (nome_p_M.find(x[j])!=nome_p_M.end())
		return j+1;
	else
		return -1;

}

int prep (int j) {
	if (preposicao.find(x[j])!=preposicao.end())
		return j+1;
	else
		return -1;
}

int artigo_f (int j) {
	if (artigo_F.find(x[j])!=artigo_F.end())
		return j+1;
	else
		return -1;
}

int artigo_p_f (int j) {
	if (artigo_p_F.find(x[j])!=artigo_p_F.end())
		return j+1;
	else
		return -1;
}

int artigo_m (int j) {
	if (artigo_M.find(x[j])!=artigo_M.end())
		return j+1;
	else
		return -1;
}

int artigo_p_m (int j) {
	if (artigo_p_M.find(x[j])!=artigo_p_M.end())
		return j+1;
	else
		return -1;
}

int verb_v (int j) {
	if (verbo_s.find(x[j]) != verbo_s.end())
		return j+1;
	else
		return -1;
}

int verb_ps (int j) {
	if (verbo_p.find(x[j]) != verbo_p.end())
		return j+1;
	else
		return -1;
}

int contracao_m (int j) {
	if (contracao_M.find(x[j]) != contracao_M.end())
		return j+1;
	else
		return -1;
}

int contracao_f (int j) {
	if (contracao_F.find(x[j]) != contracao_F.end())
		return j+1;
	else
		return -1;
} 

int contracao_p_m (int j) {
	if (contracao_p_M.find(x[j]) != contracao_p_M.end())
		return j+1;
	else
		return -1;
}

int contracao_p_f (int j) {
	if (contracao_p_F.find(x[j]) != contracao_p_F.end())
		return j+1;
	else
		return -1;
}    


int main () {
	string s;
	for(int i=0;i<28;i++){
		long start_s=clock();
		char *l = readline("String: ");
		string s = l;
		add_history(l);
		istringstream tokenStream(s);
		string token;
			while (getline(tokenStream, token, ' ')) {
				x.push_back(token);
				//printf ("%s\n", token);
			}
		sentence ();
		long stop_s=clock();
    printf("\n\nTotal time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);
    x.clear();
	}
	return 0;
}
