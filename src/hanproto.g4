grammar hanproto;

program
    : START identity (dataline)* END crc EOF ;

identity
    : HEX SPACE NUMBER TWONEWLINE;

dataline
    : TYPE SPAR data EPAR ;

data
    : time | value ;

time
    : TIME ;

value
    : FLOAT UNITMARK UNIT ;

crc
    : HEX ;

START : '/' ;
END : '!';

TWONEWLINE : '\n\n' ;

UNIT
    : 'A' | 'V' | 'kWh' | 'kVArh' | 'kW' | 'kVAr' ;

DIGIT : [0-9];
NUMBER: '-'? DIGIT+;
TIME : [0-9W]+;

TYPE : DIGIT DASH DIGIT COL NUMBER DOT DIGIT DOT DIGIT;

FLOAT : '-'? [0-9]+'.'[0-9]+;
HEX : [A-Z0-9]+;

DASH : '-';
COL : ':';
DOT : '.';
UNITMARK : '*';
SPACE : ' ';

SPAR : '(';
EPAR : ')';

WS: [ \t\n\r\f]+ -> skip ;
