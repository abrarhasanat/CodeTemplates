int GEtNumber (int x ) {  
    if(x % 2 ) return ( x + 1 ) / 2 ; 
    int cnt = Getnumberofsetbits(x)  ; 
    return  x / 2 + (cnt % 2  ?  1 :  0  )  ; 
}