<h1>Analisando uso de múltiplos núcleos de processador a partir dos comandos taskset e htop</h1>
<p>Neste diretório, você encontrará algumas capturas de tela que têm como intuito demonstrar a utilização dos comandos supracitados para analisar o comportamento dos processadores disponíveis à execução de diferentes <i>threads</i>.</p>
<p>Todas as execuções foram realizadas a partir do arquivo <code>use_cores.c</code>, disponível neste mesmo diretório.</p>
<p>O código em <code>use_cores.c</code> permite criar um determinado número de <i>threads</i>. Aplicando essa execução ao comando <code>taskset</code>, que associa os núcleos responsáveis pela execução do programa, podemos observar a utilização de diferentes núcleos, o que, aliado ao comando <code>htop</code>, que exibe os processos em execução ao usuário, nos dá informações interessantes como, por exemplo, a porcentagem do núcleo que está dedicada a determinado processo.</p>

<h1>Especificações dos processadores da máquina utilizada</h1>
<p>Consulte os arquivos <code>proc_specs.txt</code> e <code>num_cores.txt</code> para ter acesso às especificações do processador e à quantidade de núcleos, geradas a partir dos seguintes comandos:</p>

<div align="center"><code>nproc</code> e <code>cat /proc/cpuinfo</code></div>
