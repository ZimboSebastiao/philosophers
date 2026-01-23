# Philosophers

> *“Nunca pensei que um filósofo seria tão mortal.”*

## Visão Geral

O projeto **Philosophers** tem como objetivo introduzir e consolidar conceitos fundamentais de programação concorrente em C, utilizando **threads**, **mutexes** e controle rigoroso de tempo.

O problema é uma variação do clássico *Dining Philosophers*, onde filósofos alternam entre **pensar**, **comer** e **dormir**, compartilhando recursos limitados (garfos). O desafio central é evitar:

* **Deadlock** (impasse)
* **Starvation** (fome infinita)
* **Race conditions**

---

## Regras do Problema

* Cada filósofo precisa de **dois garfos** para comer
* Se um filósofo ficar mais tempo que `time_to_die` sem comer → **morre**
* As ações possíveis são:

  * `has taken a fork`
  * `is eating`
  * `is sleeping`
  * `is thinking`
  * `died`

---

## Estrutura Geral

### Entidades principais

* **Philosopher**

  * Thread individual
  * Controle de `last_meal_time`
  * Contador de refeições

* **Fork**

  * Representado por `pthread_mutex_t`

* **Monitor**

  * Thread dedicada a verificar mortes
  * Sincronizada via mutex

---

## Controle de Tempo

* Todos os tempos são calculados a partir de um `start_time`
* O `last_meal_time` é atualizado **exatamente quando o filósofo começa a comer**
* O monitor verifica constantemente:

```c
current_time - last_meal_time >= time_to_die
```

Todos os acessos a `last_meal_time` são protegidos por mutex.

---

## Concorrência e Sincronização

### Mutexes utilizados

* Mutex por garfo
* Mutex para escrita no stdout
* Mutex para controle de refeições (`meal_mutex`)

### Estratégia para evitar deadlock

* Filósofos pegam garfos em ordem consistente
* Alternância implícita garante progresso

---

## Testes

### Testes funcionais básicos

```bash
./philo 5 800 200 200
```

✔️ Nenhum filósofo morre

```bash
./philo 1 800 200 200
```

✔️ Filósofo morre após `time_to_die`

```bash
./philo 5 200 300 300
```

✔️ Morte esperada (tempo insuficiente para comer)

---

### Teste com número mínimo de refeições

```bash
./philo 5 800 200 200 7
```

✔️ Simulação termina quando todos comem 7 vezes

---

### Testes de stress

```bash
./philo 200 800 200 200
```

✔️ Sem deadlock
✔️ Sem starvation

```bash
./philo 100 410 200 200
```

✔️ Execução estável

---

## Casos de Borda (Edge Cases)

* `1` filósofo
* `time_to_die < time_to_eat`
* `time_to_die < time_to_sleep`
* Muitos filósofos simultâneos

Todos tratados corretamente.

---

## 🧹 Vazamento de Memória

### Ferramenta utilizada

```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 5 800 200 200
```

### Resultado esperado

* **0 bytes definitely lost**
* **0 bytes indirectly lost**
* Apenas memória ainda alcançável (`still reachable`) relacionada a threads do sistema

✔️ Nenhum vazamento de memória detectado

---

## Boas Práticas Aplicadas

* Todas as alocações são liberadas
* Todos os mutexes são destruídos
* Threads são corretamente `joined`
* Escrita sincronizada no terminal

---

## ✅ Conclusão

O projeto **Philosophers** foi implementado respeitando todas as regras do subject, garantindo:

* Segurança de memória
* Sincronização correta
* Execução determinística
* Robustez contra condições extremas

Este projeto demonstra domínio sólido de programação concorrente em C.

---

📌 *Projeto desenvolvido como parte do currículo da 42.*
