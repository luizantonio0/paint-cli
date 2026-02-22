# paint-cli — Paint em Terminal

Um paint simples para usar no terminal, feito em C++ para desenhar pixels, rascunhar imagens e exportar (por exemplo, como BMP). Este repositório contém um gerador de bitmap (`bitmapGenerator.cc`) e a base para uma interface terminal.

## Funcionalidades
- Desenho direto no terminal (modo pixel/brush)
- Salvamento/exportação para arquivo (ex.: BMP)
- Atalhos de teclado para desenhar, apagar e salvar
- Minimalista e leve — pensado para terminal

## Requisitos
- Compilador C++ moderno (ex.: `g++`)
- Biblioteca `ncurses` (opcional, caso a interface use ncurses)

## Build (exemplos)

Se o projeto usa apenas um arquivo fonte (ex.: `bitmapGenerator.cc`), compile com:

```bash
g++ -std=c++17 bitmapGenerator.cc -O2 -o paint
```

Se a interface usa `ncurses`, adicione o link para a biblioteca:

```bash
g++ -std=c++17 *.cc -O2 -lncurses -o paint
```

Adapte os nomes de arquivos conforme a organização do repositório.

## Uso

- Execute o binário gerado:

```bash
./paint
```

- Controles padrão (pode variar conforme a implementação):
	- Setas: mover o cursor
	- Espaço / Enter: desenhar (toggle)
	- E: apagar/borracha
	- C: limpar tela
	- S: salvar imagem (gera arquivo .bmp por exemplo)
	- Z/X: aumentar/reduzir tamanho do brush
	- H ou ?: abrir ajuda dentro do app
	- Q: sair

Se os atalhos forem diferentes na sua implementação, consulte a ajuda do aplicativo.

## Salvar / Exportar

Ao pressionar `S` (ou comando equivalente) o programa deve chamar o gerador de bitmap para criar um arquivo `.bmp` no diretório atual. Verifique `bitmapGenerator.cc` para detalhes do formato de saída e do nome do arquivo.

## Exemplos rápidos

1. Compilar (com ncurses):

```bash
g++ -std=c++17 *.cc -O2 -lncurses -o paint
```

2. Rodar:

```bash
./paint
# Dentro do app: desenhe e pressione S para salvar
```

## Contribuição

- Abra uma issue descrevendo a melhoria ou bug.
- Envie um pull request com mudanças pequenas e descritas.

## Próximos passos sugeridos
- Implementar/validar atalhos na interface
- Adicionar testes de geração de bitmap
- Melhorar ajuda/README com exemplos de tela

## Licença

Licença: escolha uma licença (ex.: MIT) e adicione um arquivo `LICENSE` se desejar permitir contribuições.

---

Se quiser, eu posso também:
- ajustar o README com comandos exatos de compilação conforme seu código atual;
- gerar um `Makefile` ou `CMakeLists.txt` minimal;
- implementar exemplos de atalhos diretamente no código.

Diga qual opção prefere que eu prossiga.

