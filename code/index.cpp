#include <iostream>

void cadastrar_paciente();
void cadastrar_medico();
void cadastrar_consulta();
void cancelar_consulta();
void relatorios();

int main(void){
    int a;
    std::cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n[1] - Cadastrar um paciente\n[2] - Cadastrar um medico\n[3] - Cadastrar uma consulta\n";
    std::cout << "[4] - Cancelar uma consulta\n[5] - Relatorios\n[0] - Sair\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\nSelecione uma opcao: ";
    std::cin >> a;
    switch (a){
        case 1:
            cadastrar_paciente();
            break;
        case 2:
            cadastrar_medico();
            break;
        case 3:
            cadastrar_consulta();
            break;
        case 4:
            cancelar_consulta();
            break;
        case 5:
            relatorios();
            break;
        case 0:
            return 0;
            break;
        default:
            main();
            break;
    }
}

void cadastrar_paciente(){
    std::cout << "\nCadastrar paciente\n";
}

void cadastrar_medico(){
    std::cout << "\nCadastrar medico\n";
}

void cadastrar_consulta(){
    std::cout << "\nCadastrar consulta\n";
}

void cancelar_consulta(){
    std::cout << "\nCancelar consulta\n";
}

void relatorios(){
    std::cout << "\nRelatorios\n";
}
