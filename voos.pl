timetable(edinburgh,london,
	[ 9:40/10:50/ba4733/alldays,
	 13:40/14:50/ba4773/alldays,
 	 19:40/20:50/ba4833/[mo,tu,we,th,fr,su]
	]).

timetable(london,edinburgh,
	[ 9:40/10:50/ba4732/alldays,
	 11:40/12:50/ba4752/alldays,
	 18:40/19:50/ba4822/[mo,tu,we,th,fr]
	]).

timetable(london,ljubljana,
	[13:20/16:20/ju201/[fr],
	 13:20/16:20/ju213/[su]
	]).

timetable(london,zurich,
	[ 9:10/11:45/ba614/alldays,
	 14:45/17:20/sr805/alldays
	]).

timetable(london,milan,
	[ 8:30/11:20/ba510/alldays,
	 11:00/13:50/az459/alldays
	]).

timetable(ljubljana,zurich,
	[11:30/12:40/ju322/[tu,th]
	]).

timetable(ljubljana,london,
	[11:10/12:20/yu200/[fr],
	 11:25/12:20/yu212/[su]
	]).

timetable(milan,london,
	[ 9:10/10:00/az458/alldays,
	 12:20/13:10/ba511/alldays
	]).

timetable(milan,zurich,
	[ 9:25/10:15/sr621/alldays,
	 12:45/13:35/sr623/alldays
	]).

timetable(zurich,ljubljana,
	[13:30/14:40/yu323/[tu,th]
	]).

timetable(zurich,london,
	[ 9:00/9:40/ba613/[mo,tu,we,th,fr,sa],
	 16:10/16:55/sr806/[mo,tu,we,th,fr,su]
	]).

timetable(zurich,milan,
	[ 7:55/8:45/sr620/alldays
	]).

days([mo,tu,we,th,fr,sa,su]).

next_day(mo,tu).
next_day(tu,we).
next_day(we,th).
next_day(th,fr).
next_day(fr,sa).
next_day(sa,su).
next_day(su,mo).

%dia n dias a frente de um Dx
next_day_n(D,0,D).
next_day_n(Dx,N,D):-N>0,Nx is N-1,next_day(Dx,Dxx),next_day_n(Dxx,Nx,D).

%check(L1,L2)
%verifica se todos elementos de L1 estão em L2
check([],_).
check([X|L],L2):-member(X,L2),check(L,L2).

route(Place1,Place2,Day,Route):-route_aux(Place1,Place2,Day,Route,[]).

route_aux(Place1,Place2,Day,Route,Vis):-
	flight(Place1,Place2,Day,Flight_num, Dep_time, _),Route = [Place1-Place2:Flight_num:Dep_time].

route_aux(Place1,Place2,Day,Route,Vis):-
	flight(Place1,PlaceX,Day,Flight_num, Dep_time, Arr_time),not(PlaceX=Place2),not(member(PlaceX,Vis)),route_aux(PlaceX,Place2,Day,RouteX,[PlaceX|Vis]),
	deptime(RouteX,D),transfer(Arr_time,D),Route=[Place1-PlaceX:Flight_num:Dep_time|RouteX].

flight(Place1, Place2, Day, Flight_num, Dep_time, Arr_time) :- timetable(Place1, Place2, L),choose_one(L,Day,Flight_num,Dep_time,Arr_time).

%escolhe um voo e coloca o direito
choose_one([(Dp_th:Dp_tm/Ar_th:Ar_tm/F_n/L_d)|_],Day,F_n,Dp_th:Dp_tm,Ar_th:Ar_tm):-member(Day,L_d),not(L_d=alldays);L_d=alldays,days(L),member(Day,L).
choose_one([_|L],Day,F,D,A):-choose_one(L,Day,F,D,A).

%verifica intervalo de 40min
transfer(H1:M1,H2:M2):-K is H1*60,K2 is K+M1,J is H2*60,J2 is J+M2,R is J2-K2,not(R<40).

%Hora de partica de uma route
deptime([_-_:_:Dep_time|_],Dep_time).

%-----------------------------------------------------------------------------------------------------------------------------------------------%
%Questions of problem%

day_flight(Place1,Place2):-
	findall(f(Day,Flight_num,Dep_time),flight(Place1,Place2,Day,Flight_num, Dep_time, _),L),
	forall(member(f(Day,Flight_num,Dep_time),L),(write(Day),write(" | "),write(Flight_num),write(" | "),writeln(Dep_time))).


available_flight(Place1,Place2,Day):-
	findall(Route,route(Place1,Place2,Day,Route),L),
	forall(member(X,L),(writeln(X))),length(L,X),X>0.


plan_visit(S,L,Ds,N):-
	member(X,L),flight(S,X,Ds,Flight_num,Dep_time,_),
	next_day(Ds,Dx),Nx is N-1,

	plan_visit_aux(X,L,[X],Dx,Nx,[K|OrderX],R),check(L,[K|OrderX]),

	next_day_n(Ds,N,Df),
	flight(K,S,Df,Flight_num2,Dep_time2,_),
	
	writeln(S-X:Flight_num:Dep_time:Ds),
	forall(member(P,R),(writeln(P))),
	writeln(K-S:Flight_num2:Dep_time2:Df),writeln("").

plan_visit_aux(_,_,Ord,_,0,Ord,[]).
plan_visit_aux(PL,L,Vis,D,N,Ord,R):-N > 0,
	member(X,L),not(member(X,Vis)),flight(PL,X,D,Flight_num,Dep_time,_),
	next_day(D,Dx),Nx is N-1,
	plan_visit_aux(X,L,[X|Vis],Dx,Nx,Ord,Rx),R=[PL-X:Flight_num:Dep_time:D|Rx].
plan_visit_aux(PL,L,Vis,D,N,Ord,R):-N > 0,next_day(D,Dx),Nx is N-1,plan_visit_aux(PL,L,Vis,Dx,Nx,Ord,R).



