#!/bin/bash


#para dar formato
ROJO=`tput setaf 1`
VERDE=`tput setaf 2`
AMARILLO=`tput setaf 3`
RESET=`tput sgr0`
SUBR=`tput smul`


#para cálculos resultados
totalLineas=0
lineasDiferentes=0
porcentajeLineas=0
MAIN_NAME=main

usage() { echo "Usage: $0 [-v]" 1>&2; exit 1; }

# Comprobar parametros de entrada
VERBOSE=false
while getopts "v" opt; do
    case "$opt" in
      v)
          VERBOSE=true
          echo VERBOSETRUE
          ;;
      *)  MAIN_NAME=$OPTARG
          if [[ "$MAIN_NAME" != "main" && "$MAIN_NAME" != "test" ]]; then
            usage
          fi
          ;;
    esac
done

ficherosEntrada=("script_minimos/eminem" "script_minimos/pruebas2")
ficherosRef=("script_minimos/eminem_ref" "script_minimos/pruebas2_ref")




# Funcion para comprobar la salida del programa
# Parametros de entrada:
#   - programa a comprobar
#   - número mínimo de salidas correctas para superar un seguimiento
#   - salida verbosa
# Parametros de salida:
#   - Exito (1) o fallo (0) en la comprobacion
function check_output {
    MAIN=$1
    MIN=$2
    DEPS=$3
    VERBOSE=$4

    rm -f ${MAIN}
    

    printf "${AMARILLO}Running script for ${LIST_TYPE_DESC} list...${RESET}"
    printf "\n${AMARILLO}Compiling "$MAIN_NAME" program with\ngcc -Wall -Wextra types.h ${DEPS} ${MAIN}.c -o ${MAIN}${RESET}\n"

    gcc -Wall -Wextra ${DEPS} ${MAIN}.c -o ${MAIN}
    
    checkpoint=1

    if [ -f ${MAIN} ]
    then
        allOK=1
        printf "\n${AMARILLO}Checking "$MAIN_NAME" program output...\n${RESET}"
	    printf "\n${SUBR}Input file${RESET}                          ${SUBR}Result${RESET}  ${SUBR}Notes${RESET}\n"
      for index in ${!ficherosEntrada[*]}
	    do
        nombre=${ficherosEntrada[$index]}
        if [ "$nombre" != "" ]
        then
	    	    ficheroEntrada="$nombre".txt
        else
            ficheroEntrada=""
            nombre="script_test/${MAIN:2:100}"
            #nombre=$index
        fi
	    	ficheroReferencia=${ficherosRef[$index]}.txt
	    	ficheroSalida="$nombre"_output.txt
	    	ficheroDiff="$nombre"_diff.txt
	    	${MAIN} $ficheroEntrada > $ficheroSalida
	    	diff -w -B -b -y --suppress-common-lines --width=170 $ficheroReferencia $ficheroSalida > $ficheroDiff
	    	iguales=$(stat -c%s $ficheroDiff)
        if [ "$ficheroEntrada" = "" ]; then
          ficheroEntrada="(no input file)"
        fi
	    	if [ ${iguales} -eq "0" ]
	    	then
	    		printf "%-35s %-12s %s\n" "$ficheroEntrada" "${VERDE}OK"  "${RESET}"
                    
	    	else
	    		printf "%-35s %-12s %s\n" "$ficheroEntrada" "${ROJO}FAIL" "${RESET}Check ${ficheroReferencia} and ${ficheroSalida}"
	    		allOK=0
	    		if [ $index -lt $MIN ]
	    		then
                    checkpoint=0
                fi
        	    if  ${VERBOSE}
    		    then
    		        printf '\nFile: %-77s |   File: %s\n' $ficheroReferencia $ficheroSalida
    		        printf '=%.0s' {1..170}
    		        printf '\n'
        			cat ${ficheroDiff}
        			printf '\n'
          	    fi
	    	fi
	    	rm $ficheroDiff
	    done
    else
   		allOK=0
      checkpoint=0
	    printf "\n${ROJO}Compilation failed${RESET}"
    fi
	printf "\n"
	
	return ${allOK}
}


function show_result {
    MESSAGE=$1
    RESULT=$2
    printf "${AMARILLO}${MESSAGE} "
    if  [ ${RESULT} -eq 1 ]
    then
        printf "${VERDE}OK${RESET}"
    else
        printf "${ROJO}FAIL${RESET}"
    fi
    printf "\n"
}


#Comprobar que existen en path actual los ficheros output de referencia
#(sino, tal y como está el script da un OK a pesar de mostrar un error en el diff)
for file in ${ficherosRef[@]}
do
	if [ ! -f "${file}.txt" ]
	then
		printf "${ROJO}Please add the reference file ${file}.txt to the current path${RESET}\n"
		exit 1
	fi
done


if [ "$MAIN_NAME" = "main" ]
then
  check_output "./main" 2 "song_list.c user_list.c" ${VERBOSE}
  MAIN_OK=${allOK}
  CHECKPOINT_OK=${checkpoint}
  show_result "Main global result:" ${MAIN_OK}
  
else
#8 de abril, primer seguimiento
  ficherosRef=("script_test/song_list_ref")
  check_output "./test_song_list" 0 "song_list.c" ${VERBOSE}
  SONG_LIST_OK=${allOK}
  show_result "Song list test:" ${SONG_LIST_OK}
  
  printf "\n"
  
  ficherosRef=("script_test/user_list_ref")
  check_output "./test_user_list" 0 "user_list.c" ${VERBOSE}
  USER_LIST_OK=${allOK}
  show_result "User list test:" ${USER_LIST_OK}
  
  printf "\n"
  
  printf "${AMARILLO}Summary:\n"
  printf "========\n"
  show_result "Song list test:" ${SONG_LIST_OK}
  show_result "User list test:" ${USER_LIST_OK}
  show_result "Tests global result (checkpoint #1 - April 12th):" $((${SONG_LIST_OK} * ${USER_LIST_OK}))
  
fi



printf "\n"
