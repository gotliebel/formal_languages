<h1 align="center">Cocke-Younger-Kasami</h1> 

# Как запускать
```shell
cmake ..
make
./cocke-younger-kasami
0 # чтобы запустить google test
```
# Пользовательский ввод
```shell
cmake ..
make
./cocke-younger-kasami
1
```
Далее ввести количество строк правил.

Сами правила в виде `S->...`.(Буквы в верхнем регистре -
нетерминалы, в нижнем - терминалы).

И само слово, которое нужно проверить