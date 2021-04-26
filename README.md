# SOA-Tarea2

Integrantes:

* Geykel Hodgson Chavarria
* Aaron Sibaja Villalobos

## Compilar proyecto 

```bash 
make
```

## Limpiar compilados

```bash 
make clean
```

## Ejecutar Programa

Para ejecutar el programa se puede hacer uso de las banderas -v y -V. La bandera -v despliega un mensaje cada vez que detecte un System Call, mientras que -V hace una pausa hasta que el usuario presione cualquier tecla para continuar la ejecucion. 

En el caso particular de que no venga ninguna bandera -v o -V se asume por default que el usuario introdujo la bandera -v. 


### Ejemplos:

```bash 
./main ls -al
```

```bash 
./main -v ls -al
```

```bash 
./main -V ls -al
```


