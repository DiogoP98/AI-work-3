sentence(X) --> frase_nom(X1), frase_verbal(X2), {X=sent(X1,X2)}.
sentence(X) --> frase_nom_p(X1), frase_verbal_p(X2), {X=sent(X1,X2)}.

frase_nom(X) --> determiner_f(X1), noun_f(X2), {X=frase_nom(determiner_f(X1), noun_f(X2))}.
frase_nom(X) --> determiner_m(X1), noun_m(X2), {X=frase_nom(determiner_m(X1), noun_m(X2))}.
frase_nom(X) --> noun_f(X1), {X=frase_nom(noun_f(X1))}.
frase_nom(X) --> noun_m(X1), {X=frase_nom(noun_m(X1))}.

frase_nom_p(X) --> determiner_p_f(X1), noun_p_f(X2), {X=frase_nom_p(determiner_p_f(X1), noun_p_f(X2))}.
frase_nom_p(X) --> determiner_p_m(X1), noun_p_m(X2), {X=frase_nom_p(determiner_p_m(X1), noun_p_m(X2))}.
frase_nom_p(X) --> noun_p_f(X1), {X=frase_nom_p(noun_p_f(X1))}.
frase_nom_p(X) --> noun_p_m(X1), {X=frase_nom_p(noun_p_m(X1))}.

frase_verbal(X) --> verb_n(X1), {X=frase_verbal(verb_n(X1))}.
frase_verbal(X) --> verb_n(X1), detn_m(X2), noun_m(X3), {X=frase_verbal(verb_n(X1), detn_m(X2), noun_m(X3))}.
frase_verbal(X) --> verb_n(X1), detn_f(X2), noun_f(X3), {X=frase_verbal(verb_n(X1), detn_f(X2), noun_f(X3))}.
frase_verbal(X) --> verb_n(X1), detn_p_m(X2), noun_p_m(X3), {X=frase_verbal(verb_n(X1), detn_p_m(X2), noun_p_m(X3))}.
frase_verbal(X) --> verb_n(X1), detn_p_f(X2), noun_p_f(X3), {X=frase_verbal(verb_n(X1), detn_p_f(X2), noun_p_f(X3))}.
frase_verbal(X) --> verb_v(X1), {X=frase_verbal(verb_v(X1))}.
frase_verbal(X) --> verb_v(X1), detv_m(X2), noun_m(X3), {X=frase_verbal(verb_v(X1), detv_m(X2), noun_m(X3))}.
frase_verbal(X) --> verb_v(X1), detv_f(X2), noun_f(X3), {X=frase_verbal(verb_v(X1), detv_f(X2), noun_f(X3))}.
frase_verbal(X) --> verb_v(X1), detv_p_m(X2), noun_p_m(X3), {X=frase_verbal(verb_v(X1), detv_p_m(X2), noun_p_m(X3))}.
frase_verbal(X) --> verb_v(X1), detv_p_f(X2), noun_p_f(X3), {X=frase_verbal(verb_v(X1), detv_p_f(X2), noun_p_f(X3))}.

frase_verbal_p(X) --> verb_p_n(X1), {X=frase_verbal_p(verb_p_n(X1))}.
frase_verbal_p(X) --> verb_p_n(X1), detn_p_m(X2), noun_p_m(X3), {X=frase_verbal_p(verb_p_n(X1), detn_p_m(X2), noun_p_m(X3))}.
frase_verbal_p(X) --> verb_p_n(X1), detn_p_f(X2), noun_p_f(X3), {X=frase_verbal_p(verb_p_n(X1), detn_p_f(X2), noun_p_f(X3))}.
frase_verbal_p(X) --> verb_p_n(X1), detn_m(X2), noun_m(X3), {X=frase_verbal_p(verb_p_n(X1), detn_m(X2), noun_m(X3))}.
frase_verbal_p(X) --> verb_p_n(X1), detn_f(X2), noun_f(X3), {X=frase_verbal_p(verb_p_n(X1), detn_f(X2), noun_f(X3))}.
frase_verbal_p(X) --> verb_p_v(X1), {X=frase_verbal_p(verb_p_v(X1))}.
frase_verbal_p(X) --> verb_p_v(X1), detv_p_m(X2), noun_p_m(X3), {X=frase_verbal_p(verb_p_v(X1), detv_p_m(X2), noun_p_m(X3))}.
frase_verbal_p(X) --> verb_p_v(X1), detv_p_f(X2), noun_p_f(X3), {X=frase_verbal_p(verb_p_v(X1), detv_p_f(X2), noun_p_f(X3))}.
frase_verbal_p(X) --> verb_p_v(X1), detv_m(X2), noun_m(X3), {X=frase_verbal_p(verb_p_v(X1), detv_m(X2), noun_m(X3))}.
frase_verbal_p(X) --> verb_p_v(X1), detv_f(X2), noun_f(X3), {X=frase_verbal_p(verb_p_v(X1), detv_f(X2), noun_f(X3))}.


determiner_m(X)   --> [o], {X=o}; ['O'], {X='O'}.
determiner_f(X)   --> [a], {X=a}; ['A'], {X='A'}.

determiner_p_m(X) --> [os], {X=os}; ['Os'], {X='Os'}.
determiner_p_f(X) --> [as], {X=as}; ['As'], {X='As'}.

noun_m(X)    --> [tempo], {X=tempo}; [cacador], {X=cacador}; [rosto], {X=rosto}; [rio], {X=rio}; [mar], {X=mar}; [martelo], {X=martelo}; [cachorro], {X=cachorro}; [tambor], {X=tambor}; [sino], {X=sino}; [lobo], {X=lobo}; [vento], {X=vento}.
noun_p_m(X)  --> [cacadores], {X=cacadores}; [rostos], {X=rostos}; [rios], {X=rios}; [mares], {X=mares}; [martelos], {X=martelos}; [cachorros], {X=cachorros}; [tambores], {X=tambores}; [sinos], {X=sinos}; [lobos], {X=lobos}; [ventos], {X=ventos}.

noun_f(X)    --> [menina], {X=menina}; [floresta], {X=floresta}; [mae], {X=mae}; [vida], {X=vida}; [noticia], {X=noticia}; [cidade], {X=cidade}; [lagrima], {X=lagrima}; [porta], {X=porta}.
noun_p_f(X)  --> [meninas], {X=meninas}; [florestas], {X=florestas}; [maes], {X=maes}; [vidas], {X=vidas}; [noticias], {X=noticias}; [cidades], {X=cidades}; [lagrimas], {X=lagrimas}; [portas], {X=portas}.

verb_n(X)    --> [bate], {X=bate}; [bateu], {X=bateu}.
verb_p_n(X)  --> [bateram], {X=bateram}; [batiam], {X=batiam}; [batem], {X=batem}.

verb_v(X)    --> [corre], {X=corre}; [correu], {X=correu}.
verb_p_v(X)  --> [correram], {X=correram}; [corriam], {X=corriam}; [correm], {X=correm}.

detn_m(X)    --> [no], {X=no}; [o], {X=o}.
detn_p_m(X)  --> [nos], {X=nos}; [os], {X=os}.

detn_f(X)    --> [na], {X=na}; [a], {X=a}.
detn_p_f(X)  --> [nas], {X=nas}; [as], {X=a}.

detv_m(X)    --> [com], [o], {X=[com,o]}; [pelo], {X=pelo}; [para], [o], {X=[para,o]}.
detv_p_m(X)  --> [com], [os], {X=[com,os]}; [pelos], {X=pelos}; [para], [os], {X=[para,os]}.

detv_f(X)    --> [com], [a], {X=[com,as]}; [pela], {X=pela}; [para], [a], {X=[para,a]}.
detv_p_f(X)  --> [com], [as], {X=[com,as]}; [pelas], {X=pelas}; [para], [as], {X=[para,as]}.

