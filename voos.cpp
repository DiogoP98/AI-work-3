#include <bits/stdc++.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctime>
#include <unistd.h>

using namespace std;

//mehtod for classes
int convert_dia (string p);
void convert (string p1, string p2, string p);

//classes
//Estrutura para guardar voos
class Flight{
public:
  string Place1;
  string Place2;
  int hourDeparture;
  int minutesDeparture;
  int hourArrival;
  int minutesArrival;
  string number;
  vector<bool> days; //array que guarda em que dias o voo esta dipsonivel

  Flight(string P1, string P2, int hp, int minp, int hc, int minc, string n, vector<bool> d){
    this->Place1=P1;
    this->Place2=P2;
    this->hourDeparture=hp;
    this->minutesDeparture=minp;
    this->hourArrival=hc;
    this->minutesArrival=minc;
    this->number = n;
    this->days=d;
  }

  string getstring () {
		string res = "";
		res+=this->Place1+"-"+this->Place2+": "+this->number+": ";
		if(this->hourDeparture<=9)res+="0";
		res+=to_string(this->hourDeparture)+":";
		if(this->minutesDeparture<=9)res+="0";
		res+=to_string(this->minutesDeparture);
		return res;
  }
};

//Estrutura para guardar timtables
class timetable{
public:
  string P1;
  string P2;
  vector<Flight*> f; 

  timetable(string p1, string p2, vector<string> x) {
    //cout << ("p1=%s p2=%s", p1.c_str(), p2.c_str());
    this->P1 = p1;
    this->P2 = p2;
    for (int i=0; i<(int)x.size();i++) {
      //cout << ("x[i]=%s\n", x[i]);
      convert(p1,p2,x[i]);
      //cout << ("1ºciclo\n");
    }
  }

  void convert (string p1, string p2, string p) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(p);
    while (getline(tokenStream, token, '/')) {
      tokens.push_back(token);
      //cout << ("%s\n", token);
    }
  

    string number = tokens[2]; //numero do aviao
    //cout << ("number = %s\n", number);
    istringstream tokenStream2(tokens[0]); //para separar o horario de partida
    istringstream tokenStream3(tokens[1]); //para separar o horario de chegada

    vector<int> times;
    while (getline(tokenStream2, token, ':')) {
      times.push_back(stoi(token));
    }

    while (getline(tokenStream3, token, ':')) {
      times.push_back(stoi(token));
    }

    int hp = times[0]; //hora de partida
    int mp = times[1]; //minutos de partida
    int hc = times[2]; //hora de chegada
    int mc = times[3]; //minutos de chegadao

    if (tokens[3] == "alldays") {
      vector<bool> dias (7,true);
      Flight *a = new Flight (p1,p2,hp,mp,hc,mc,number,dias);
      this->f.push_back(a);
    }
    else {
      //int i=0;
      vector<bool> dias(7,false);
      //cout << ("here2\n");
      tokens[3].erase(remove(tokens[3].begin(), tokens[3].end(), '['), tokens[3].end());
      tokens[3].erase(remove(tokens[3].begin(), tokens[3].end(), ']'), tokens[3].end());
      istringstream tokenStream(tokens[3]);
      while (getline(tokenStream, token, ',')){ 
	      dias [convert_dia(token)] = true;
        //if (p1=="ljubljana" && p2 == "london")
        //  cout << ("%s\n",token.c_str());
      }
      Flight *a = new Flight (p1,p2,hp,mp,hc,mc,number,dias);
        this->f.push_back(a);
    }

  }
};

//global variables
int op;
char *l;

//data structures
vector <timetable*> timetables;
vector<Flight*> route_res;
vector<Flight*> plan_res;

//methods
bool route (string p1, string p2, int day);
bool plan_visit (string s, vector<string> v, int day,int n);
bool transfer (int h1 , int m1, int h2, int m2);
vector<Flight*> flight (string p1, string p2,int day);
string convert_int(int j);
int value();
string value2 ();

int main () {
	{
  string s1= "edinburgh";
  string s2 = "london";
  vector<string> x = {" 9:40/10:50/ba4733/alldays","13:40/14:50/ba4773/alldays","19:40/20:50/ba4833/[mo,tu,we,th,fr,su]"};
  timetable* u= new timetable(s1,s2,x);
  timetables.push_back(u);

  s1="london";
  s2="ljubljana";
  x= {"13:20/16:20/ju201/[fr]","13:20/16:20/ju213/[su]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "london";
  s2 = "edinburgh";
  x = { " 9:40/10:50/ba4732/alldays",
 "11:40/12:50/ba4752/alldays",
   "18:40/19:50/ba4822/[mo,tu,we,th,fr]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "london";
  s2 = "zurich";
  x = {" 9:10/11:45/ba614/alldays",
 "14:45/17:20/sr805/alldays"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "london";
  s2 = "milan" ;
  x = 	{" 8:30/11:20/ba510/alldays",
 "11:00/13:50/az459/alldays"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "ljubljana";
  s2 = "zurich";
  x = {"11:30/12:40/ju322/[tu,th]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "ljubljana";
  s2 = "london";
  x = {"11:10/12:20/yu200/[fr]",
 "11:25/12:20/yu212/[su]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "milan";
  s2 = "london";
  x = {" 9:10/10:00/az458/alldays",
 "12:20/13:10/ba511/alldays"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "milan";
  s2 = "zurich";
  x = {" 9:25/10:15/sr621/alldays",
 "12:45/13:35/sr623/alldays"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "zurich";
  s2 = "ljubljana";
  x = {"13:30/14:40/yu323/[tu,th]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "zurich";
  s2 = "london";
  x = {" 9:00/9:40/ba613/[mo,tu,we,th,fr,sa]",
   "16:10/16:55/sr806/[mo,tu,we,th,fr,su]"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);

  s1 = "zurich";
  s2 = "milan";
  x = {" 7:55/8:45/sr620/alldays"};
  u=new timetable(s1,s2,x);
  timetables.push_back(u);
	}
  
  cout << ("Menu:\n");
  cout << ("(1) Get Days of a Flight\n(2) Search Available Flights by day\n(3) Search Circuits\n(0) Leave\n");
  l = readline ("Choose you option: ");
  add_history(l);
  op = value ();
  while (op != 0) {

    if (op == 1) {
      long start_s=clock();
			string p1,p2;
			
      l = readline ("Departure Place: ");
      add_history(l);
      p1= value2();
      l = readline ("Destination: ");
      add_history(l);
      p2 = value2 ();    
      cout << ("\n");
      bool p = false;
      
      for(int i=0;i<7;i++){
				vector<Flight*> f = flight (p1,p2,i);
				if(f.size()>0){
					for(int j=0;j<(int)f.size();j++) cout << f[j]->getstring() << " on " + convert_int(i) <<endl;
					p = true;
				} 
			}
      
      if(!p) cout << "We apologize but there are no direct flights from "+p1+" to "+p2+"\n";

      long stop_s=clock();
      printf("\nTotal time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);

      cout << ("\n\nDo you want do search for anything else?\n");
    }

		else if (op == 2) {
      long start_s=clock();

      string p1,p2,day;
      int d;
      
      l = readline("Departure Place: ");
      add_history(l);
      p1 = value2();
      l = readline ("Destination: ");
      add_history(l);
      p2 = value2 ();
      l = readline ("Day: ");
      add_history(l);
      day = value2 ();
      d = convert_dia(day);
      if(d == -1){
        l = readline ("Invalid Day! Day: ");
        add_history(l);
        day = value2 ();
        d = convert_dia(day);
      }
      bool k = route (p1,p2,d);
      cout <<("\n");
      if (!k) 
        cout << "There are no flights from "+p1+" to "+p2+" on "+ convert_int (d) +"\n";
      else
          for(int i=0;i<(int)route_res.size();i++) cout << route_res[i]->getstring()<<endl;
      route_res.clear();

      long stop_s=clock();
      printf("\nTotal time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);

      cout << ("\n\nDo you want do search for anything else?\n");
    }

    else if (op == 3) {

      string s, p1;
      int n;
      vector<string> v;
      l = readline ("Starting place: ");
      add_history(l);
      s = value2();

      l= readline ("Number of cities to visit: ");
      add_history(l);
      n = value();

      if(n < 0 || n > 7){
        l = readline ("Invalid number! Try again: ");
        add_history(l);
        n = value();
      }

      for (int i=0;i<n;i++) {
        printf ("City %d:", i+1);
        fflush(stdin);
        l = readline (" ");
        add_history(l);
        p1 = value2();
        //cout << "City : " + s + "\n" ;
        v.push_back(p1);
      }

      int d1;
      
      l = readline ("Departure day: ");
      add_history(l);
      string day1 = value2 ();
      d1 = convert_dia(day1);
      if(d1 == -1){
				l = readline ("Invalid Day! Departure day: ");
				add_history(l);
				day1 = value2 ();
				d1 = convert_dia(day1);
			}
      
			long start_s=clock();
      bool k = plan_visit(s,v,d1,n);
      cout <<("\n");
      if (!k)
      	cout << ("No visit plan found\n");
      else
					for(int i=0;i<(int)plan_res.size();i++) cout << plan_res[i]->getstring() + " on " + convert_int ((d1+i)%7)<<endl;
      plan_res.clear();

      long stop_s=clock();
      printf("\nTotal time thinking: %lf\n",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);

      cout << ("\n\nDo you want do search for anything else?\n");
    }

    else {
      cout << ("Wrong option try again\n");
    }

    cout << ("(1) Get Days of a Flight\n(2) Search Available Flights by day\n(3) Search Circuits\n(0) Leave\n");
		l = readline ("Choose you option: ");
    add_history(l);
    op = value();  

  }

  return 0;
}

//verifica se place esta no vetor de flights
bool check(string place,vector<Flight*> v){
	for(int i=0;i<(int)v.size();i++){
		if(v[i]->Place2 == place) return false;
	}
	return true;
}

//cria route de p1 para p2 no dia day recursivamente e guarda o resultado no vector route_res
bool route (string p1, string p2, int day){
	int arh = 0,arm=0;
	if(route_res.size()>0){
		arh = route_res.back()->hourArrival;
		arm = route_res.back()->minutesArrival;
	}
	vector<Flight*> f = flight(p1,p2,day);
	
	for(int i=0;i<(int)f.size();i++){
		if(transfer(arh,arm,f[i]->hourDeparture,f[i]->minutesDeparture)){
			route_res.push_back(f[i]);
			return true;
		}
	}
	
	f.clear();
	
	vector<string> v;
	for(int i=0;i<(int)timetables.size();i++){
		if(timetables[i]->P1 == p1 && check(timetables[i]->P2,route_res)){
			f = flight(p1,timetables[i]->P2,day);
			for(int j=0;j<(int)f.size();j++){
				if(transfer(arh,arm,f[j]->hourDeparture,f[j]->minutesDeparture)){
					route_res.push_back(f[j]);
					if(route(timetables[i]->P2,p2,day))				
						return true;
					route_res.pop_back();
				}
			}
		}
	}
	return false;
}

//cria circuit de s para s que passe pelas cidades em v e comece no dia day recursivamente e guarda o resultado no vector plan_res
bool plan_visit (string s, vector<string> v, int day,int n){
	vector<Flight*> f;
	
	if((int)plan_res.size()==n){
		f=flight(plan_res.back()->Place2,s,day);
		if(f.size()>0){
			plan_res.push_back(f[0]);
			return true;
		}
		else return false;
	}
	
	for(int i=0;i<(int)v.size();i++){
		if(plan_res.size()==0) f = flight(s,v[i],day);
		else f = flight(plan_res.back()->Place2,v[i],day);
		if((check(v[i],plan_res) && f.size()>0) || (plan_res.size()==0 && f.size()>0)){
			plan_res.push_back(f[0]);
			if(plan_visit(s,v,(day+1)%7,n)) return true;
			plan_res.pop_back();
		}
	}
	return false;
}

//verifica se ha voo direto de cidade p1 para p2 no dia day
vector<Flight*> flight (string p1, string p2,int day) {
  timetable* k;
  Flight* r;
  vector<Flight*> res;
  for (int i = 0; i < (int)timetables.size();i++) {
    k = timetables[i];
    if (k->P1 == p1 && k->P2 == p2) {
      for (int j = 0; j< (int) k->f.size(); j++) {
        r = k->f[j];
        if(r->days[day]) res.push_back(r);
      }
    }
  }
	return res;
}

//converte opcao do menu
int value(){
  if(l==NULL)
    return -1;
  if(!isdigit(l[0]))
    return -1;
  int k = atoi(l);
  if(k<0 || k>4) 
    return 0;
  return k;
} 

//converte string e verifica a
string value2 () {
  if (l==NULL)
    return NULL;
  string str(l);
  return str;
}

//verifica intervalo de 40min
bool transfer (int h1 , int m1, int h2, int m2) {
	int x1 = h1*60+m1;
	int x2 = h2*60+m2;
	return (x2-x1)>=40;
}

string convert_int (int j) {
  if (j == 0) 
    return "Monday";
  else if (j == 1)
    return "Tuesday";
  else if (j ==2)
    return "Wednesday";
  else if (j == 3) 
    return "Thursday";
  else if (j == 4) 
    return "Friday";
  else if (j == 5)
    return "Saturday";
  else
    return "Sunday";
}

int convert_dia (string p) {
  if (p == "mo") 
    return 0;
  else if (p == "tu")
    return 1;
  else if (p =="we")
    return 2;
  else if (p == "th") 
    return 3;
  else if (p == "fr") 
    return 4;
  else if (p == "sa")
    return 5;
  else if (p == "su")
    return 6;
  else
    return -1;
}

