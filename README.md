# Pomodoro em C 
#### Contador pomodoro feito em c, que pode ser utilizado para contabilizar o tempo de cada atividade. Ele por padrão é definido com *25* minutos, mas que pode ser alterado atraves dos argumentos. Ele gera um *log.csv* no final do tempo com as informações de: data, hora, nome e tempo da ativade.  

**basta compilar:** *gcc main.c -o main*  
**depois executar:** *./main* [Argumentos, caso queira usar]

### **Argumentos:**  
* **"-h" ou "--help":**  
Mostra no terminal as informações dos comandos e suas funções.  

* **"-n" ou "--name":**  
Define o nome da ativade que ficará gravada no log (pomodoro é o nome padrão).  
ex.: "-n estudar"

* **"-t" ou "--time":**  
Define o tempo da atividade em minutos (25 minutos é o padrão).  
ex.: "-t 25"

**Exemplo de saida do arquivo log.csv: *"1.1.2024; 17:30:50; Pomodoro; 25"*.**  
**No final do tempo ele exibe 10 beeps avisando que a atividade terminou.**
