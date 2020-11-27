
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Registro();
void Lista();
void Dia();
void Nevento();
void Meses(int nm);
void Horario();
void Mevento();
void Eliminar();

struct Fecha{
    int d;
    int m;
    int a;
};

struct Evento{
    struct Fecha fecha;
    int hora;
    int minuto;
    int tiempo;
    char evento[100];
    char lugar[100];
    char tema[100];
}leer[1000],n,c;

FILE*archivo;

int main() {
    int n;
    
    while(n!=8){
        printf("¿Qué es lo que desea realizar?\n");
        printf("1. Registrar un evento\n");
        printf("2. Modificar nombre del evento\n");
        printf("3. Modificar horario del evento\n");
        printf("4. Eleminar evento\n");
        printf("5. Lista de todos los eventos\n");
        printf("6. Consultar los eventos de un dia\n");
        printf("7. Buscar eventos por nombre\n");
        printf("8. Salir\n");
        scanf("%d",&n);
    
        switch(n){
            case 1: Registro(); break;
            case 2: Mevento(); break;
            case 3: Horario(); break;
            case 4: Eliminar(); break;
            case 5: Lista(); break;
            case 6: Dia(); break;
            case 7: Nevento(); break;
        }
    }
    
    return 0;
}

void Registro(){
    char registro;
    
    archivo=fopen("datos.dat","ad");
    printf("Introduzca la fecha en números\n");
    printf("Día: "); 
    scanf("%d",&n.fecha.d);
    printf("Mes: ");
    scanf("%d",&n.fecha.m);
    printf("Año: ");
    scanf("%d",&n.fecha.a);
    printf("\nHora:\nEjemplo: 16:30\n");
    scanf("%d:%d",&n.hora,&n.minuto);
    printf("\nDuración del evento en minutos: ");
    scanf("%d",&n.tiempo);
    
    scanf("%c",&registro);
    printf("\nNombre del evento: ");
    scanf("%[^\n]",&n.evento);
    
    scanf("%c",&registro);
    printf("\nLugar: ");
    scanf("%[^\n]",&n.lugar);

    scanf("%c",&registro);
    printf("\nTema: ");
    scanf("%[^\n]",&n.tema);
    fwrite(&n,sizeof(struct Evento),1,archivo);
    fclose(archivo);
}

void Lista(){
    
    int nm2=0;
    int nm3=0;
    int nm4=0;
    int nm5=0;
    
    
    archivo=fopen("datos.dat","rd");
    while(feof(archivo)==0){
        fread(&leer[nm2],sizeof(leer[nm2]),1,archivo);
        nm2++;       
    }
    
    nm2=nm2-2;
    
        while(nm3<nm2){
            nm4=nm2;
            while(nm3<nm4){
                if((leer[nm4].fecha.a)<(leer[nm3].fecha.a)){
                    c=leer[nm4];
                    leer[nm4]=leer[nm3];
                    leer[nm3]=c;
                }
                
                if((leer[nm4].fecha.a)==(leer[nm3].fecha.a)){
                    if((leer[nm4].fecha.m)<(leer[nm3].fecha.m)){
                        c=leer[nm4];
                        leer[nm4]=leer[nm3];
                        leer[nm3]=c;
                    }
                    if((leer[nm4].fecha.m)==(leer[nm3].fecha.m)){
                        if((leer[nm4].fecha.d)<(leer[nm3].fecha.d)){
                            c=leer[nm4];
                            leer[nm4]=leer[nm3];
                            leer[nm3]=c;
                        }
                        if((leer[nm4].fecha.d)==(leer[nm3].fecha.d)){
                            if((leer[nm4].hora)<(leer[nm3].hora)){
                                c=leer[nm4];
                                leer[nm4]=leer[nm3];
                                leer[nm3]=c;
                            }
                            if((leer[nm4].hora)==(leer[nm3].hora)){
                                if((leer[nm4].minuto)<(leer[nm3].minuto)){
                                    c=leer[nm4];
                                    leer[nm4]=leer[nm3];
                                    leer[nm3]=c;
                                }
                            }
                        }
                    }
                }
           
                nm4--;
            }
            nm3++;
        }    
    
    nm3=0;
    printf("FECHA\t\tHORA\t\tEVENTO\n");
    
    struct Evento prueba[1000];
    FILE*eliminar;
    eliminar=fopen("eliminar.dat","rd");
    
    while(feof(eliminar)==0){
        fread(&prueba[nm5],sizeof(prueba[nm5]),1,eliminar);
        nm5++;
    }
    fclose(eliminar);
    int nm6=nm5;
    
    while(nm3<(nm2+1)){
        nm5=nm6;
        while(0<=nm5){
            if (strcmp(prueba[nm5].evento, leer[nm3].evento)==0){
                goto final;         
            }
            nm5--;        
        }
        printf("%d/%d/%d\t",leer[nm3].fecha.d,leer[nm3].fecha.m,leer[nm3].fecha.a);
        printf("%d:%d\t\t%s\n",leer[nm3].hora,leer[nm3].minuto,leer[nm3].evento); 
        final:
        nm3++;
    }
    printf("\n");
    fclose(archivo);
}

void Dia(){
    int dia,mes,anio;
    int nm=0;
    int m=0;

    printf("Ingrese la fecha que le gustaría consultar\n");
    printf("Dia: ");
    scanf("%d",&dia);
    printf("Mes: ");
    scanf("%d",&mes);
    printf("Año: ");
    scanf("%d",&anio);
    
    archivo=fopen("datos.dat","rd");
    
    printf("\n");
    while(feof(archivo)==0){
        fread(&leer[nm],sizeof(leer[nm]),1,archivo);
        nm++;
    }
    
    printf("FECHA\t\tHORA\t\tEVENTO\n");
    while(m<nm){
        
        if ((dia==leer[m].fecha.d) && (mes==leer[m].fecha.m) && (anio==leer[m].fecha.a)){
            printf("%d/%d/%d\t",leer[m].fecha.d,leer[m].fecha.m,leer[m].fecha.a);
            printf("%d:%d\t\t%s\n",leer[m].hora,leer[m].minuto,leer[m].evento);
        }
        m++;
    }
    
    fclose(archivo);
    printf("\n");
}

void Nevento(){
    int nm=0;
    char nombre[100];
    char registro;
    
    printf("\nIngrese el nombre del evento\n");
    scanf("%c",&registro);
    scanf("%[^\n]",&nombre);
    
    archivo=fopen("datos.dat","rd");
    while(feof(archivo)==0){
        fread(&leer[nm],sizeof(leer[nm]),1,archivo);
        if (strcmp(nombre, leer[nm].evento)==0){
            printf("\n\nDATOS DEL EVENTO\n\n");            
            printf("FECHA: %d de ",leer[nm].fecha.d);
            Meses(leer[nm].fecha.m);
            printf(" de %d\n",leer[nm].fecha.a);
            printf("HORA: %d:%d hrs\n",leer[nm].hora,leer[nm].minuto);
            printf("DURACIÓN: %d minutos\n",leer[nm].tiempo);
            printf("EVENTO: %s\n",leer[nm].evento);
            printf("LUGAR: %s\n",leer[nm].lugar);
            printf("TEMA: %s\n\n",leer[nm].tema);
            fclose(archivo);
            return 0;
        }
        nm++;
    }
    fclose(archivo);
    printf("\n\nNo se encontro ningun evento con este nombre\n\n");
    
}

void Meses(int nm){
    switch(nm){
        case 1: printf("enero"); break;
        case 2: printf("febrero"); break;
        case 3: printf("marzo"); break;
        case 4: printf("abril"); break;
        case 5: printf("mayo"); break;
        case 6: printf("junio"); break;
        case 7: printf("julio"); break;
        case 8: printf("agosto"); break;
        case 9: printf("septiembre"); break;
        case 10: printf("octubre"); break;
        case 11: printf("noviembre"); break;
        case 12: printf("diciembre"); break;
    }    
}

void Horario(){
    int nm=0;
    char nombre[100];
    char registro;
    int hora,min;
    
    Lista();
    printf("Ingresa el evento donde quiera cambiar la hora\n");
    scanf("%c",&registro);
    scanf("%[^\n]",&nombre);
    archivo=fopen("datos.dat","r+d");
    while(feof(archivo)==0){
        fread(&leer[nm],sizeof(leer[nm]),1,archivo);
        if (strcmp(nombre, leer[nm].evento)==0){
            
            printf("\n\nFECHA:");
            printf("%d/%d/%d\n",leer[nm].fecha.d,leer[nm].fecha.m,leer[nm].fecha.a);
            printf("EVENTO: %s\nHORA:%d:",leer[nm].evento, leer[nm].hora);
            
            int posh= ftell(archivo)-sizeof(leer[nm]);
            printf("%d\n\n",leer[nm].minuto);
            printf("Modificacion\n");
            printf("Ejemplo 16:30 \n");
            printf("Nuevo horario: \n");
            scanf("%d:%d",&leer[nm].hora,&leer[nm].minuto);
                        
            fseek(archivo,posh,SEEK_SET);
            fwrite(&leer[nm],sizeof(leer[nm]),1,archivo);
            
            fclose(archivo);
            printf("\n\n");
            return 0;
        }
        nm++;
    }
    printf("\n\nIngresó mal el nombre\n");
    fclose(archivo);
}

void Mevento(){
    int nm=0;
    char nombre[100];
    char registro;
    int hora,min;
    
    Lista();
    printf("Ingresa el evento donde quiera cambiar el nombre del evento\n");
    scanf("%c",&registro);
    scanf("%[^\n]",&nombre);
    archivo=fopen("datos.dat","r+d");
    while(feof(archivo)==0){
        fread(&leer[nm],sizeof(leer[nm]),1,archivo);
        if (strcmp(nombre, leer[nm].evento)==0){
            
            printf("\n\nFECHA:");
            printf("%d/%d/%d\n",leer[nm].fecha.d,leer[nm].fecha.m,leer[nm].fecha.a);
            printf("EVENTO: %s\nHORA:%d:",leer[nm].evento, leer[nm].hora);
            
            int posh= ftell(archivo)-sizeof(leer[nm]);
            printf("%d\n\n",leer[nm].minuto);
            printf("Modificacion\n");
            printf("Ingrese el nuevo nombre del evento:\n");
            scanf("%c",&registro);
            scanf("%[^\n]",&leer[nm].evento);
                        
            fseek(archivo,posh,SEEK_SET);
            fwrite(&leer[nm],sizeof(leer[nm]),1,archivo);
            
            fclose(archivo);
            printf("\n\n");
            return 0;
        }
        nm++;
    }
    printf("\n\nIngresó mal el nombre\n");
    fclose(archivo);
}

void Eliminar(){
    int nm=0;
    char nombre[100];
    char registro;
    int hora,min;
    int decidir;
    
    FILE*eliminar;
    
    Lista();
    printf("Ingresa el evento que quiera eliminar\n");
    scanf("%c",&registro);
    scanf("%[^\n]",&nombre);
    archivo=fopen("datos.dat","rd");
    
    eliminar=fopen("eliminar.dat","ad");
    while(feof(archivo)==0){
        fread(&leer[nm],sizeof(leer[nm]),1,archivo);
        if (strcmp(nombre, leer[nm].evento)==0){
            
            printf("\n\nFECHA:");
            printf("%d/%d/%d\n",leer[nm].fecha.d,leer[nm].fecha.m,leer[nm].fecha.a);
            printf("EVENTO: %s\nHORA:%d:",leer[nm].evento, leer[nm].hora);
            
            printf("%d\n\n",leer[nm].minuto);
            printf("¿Está seguro?\n");
            printf("1. Si\n2. No\n");
            scanf("%d",&decidir);
            if(decidir==2){
                printf("\nNo se ha eliminado\n\n");
                fclose(eliminar);
                return 0;
            }
                        

            fwrite(&leer[nm],sizeof(leer[nm]),1,eliminar);
            fclose(eliminar);
            fclose(archivo);
            printf("\nEl evento se ha eliminado\n\n");
            return 0;
        }
        nm++;
    }
    printf("\n\nIngresó mal el nombre\n");
    fclose(archivo);
}