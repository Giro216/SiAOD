#include "header.h"

int main()
{
    Enterprise** array_pointer = new Enterprise * [4000];
    read_bd(array_pointer);
    menu(array_pointer);    

}

void menu(Enterprise** arr)
{
    int button = 0;
    bool button3 = false;
    bool button4 = false;
    queue queue_of_found;

    while (button != 6)
    {
        switch (button)
        {
        case(0):
        {
            system("CLS");
            cout << "1\t" << "Print bd" << endl;
            cout << "2\t" << "Sort & write bd" << endl;
            cout << "3\t" << "Search" << endl;
            cout << "4\t" << "Tree" << endl;
            cout << "5\t" << "Code bd" << endl;
            cout << "6\t" << "EXIT" << endl;

            cin >> button;
            break;
        }
        case(1):
        {
            print_bd(arr);
            button = 0;
            break;
        }
        case(2):
        {
            system("CLS");
            cout << "Sorting..." << endl;
            HeapSort_bd(arr);
            print_bd(arr);
            button = 0;
            break;
        }
        case(3):
        {
            system("CLS");

            int key;
            cout << "Enter date of birthday" << endl;
            cin >> key;

            int found = bin_search(arr, key);
            queue_of_found = create_queue(arr, found, key);
            print_queue(&queue_of_found);

            button3 = true;
            button = 0;
            break;
        }
        case(4):
        {
            if (button3 == false) {
                cout << "ERROR" << endl;
                cout << "Search something before creating a tree" << endl;
                cout << "Press any key to continue" << endl;
                int esc = _getch();
                button = 3;
                break;
            }

            B2_Tree* root = NULL;
            create_tree(root, &queue_of_found);
            print_tree(root);

            unsigned short dep_number;
            int KB_code = 0;
            while (KB_code != KB_ESCAPE)
            {
                cout << "To search, write a dep_number" << endl;
                cin >> dep_number;
                B2_Tree* founded_root = tree_search(dep_number, root);

                if (founded_root == NULL) {
                    cout << "Key didn't found" << endl;
                }
                else {
                    spis* temp = founded_root->equal_items;

                    cout << founded_root->data.name << "\t" << founded_root->data.job << "\t" << founded_root->data.dep_number << "\t" << founded_root->data.date << endl;
                    while (temp != NULL)
                    {
                        cout << temp->data.name << "\t" << temp->data.job << "\t" << temp->data.dep_number << "\t" << temp->data.date << endl;
                        temp = temp->next;
                    }
                }

                cout << "\nTo search other dep_number press any key" << endl;
                cout << "But to exit press Esc\n" << endl;
                KB_code = _getch();
            }

            system("CLS");
            button = 0;
            break;
        }
        case(5): 
        {
            system("CLS");
            int KB_code = 0;
            while (KB_code != KB_ESCAPE)
            {
                Huffman_code(arr);
                cout << "To exit press Esc\n" << endl;
                KB_code = _getch();
            }
            button = 0;
            break;
        }
        default:
            system("CLS");
            button = 0;
            cout << "ERROR: you whrote a wrong number" << endl;
            cout << "       Please try again" << endl;
            break;
        }
    }
}

void read_bd(Enterprise** arr)
{
    ifstream bd("obj/testBase2.dat", ios::binary);
    if (bd.is_open())
    {
        int count = 0;
        while (!bd.eof())
        {
            arr[count] = new Enterprise;
            bd.read((char*)arr[count], sizeof(*arr[count]));
            count++;
        }

        bd.close();
    }
    else
    {
        cout << "Error opening file!" << endl;
        exit(-1);
    }
}

void print_bd(Enterprise** arr)
{
    short int count = 0;
    int KB_code = 0;
    system("CLS");
    cout << "choose format of printing bd: by 20 items (<- or ->) or full bd (pgdn)" << endl;
    while (KB_code != KB_ESCAPE)
    {
        cout << "\nTo exit press Esc" << endl;
        KB_code = _getch();
        system("CLS");
        switch (KB_code)
        {
        case(KB_RIGHT):
        {
            if (count >= 3999) {
                cout << "it's a finish of bd." << endl;
                break;
            }
            for (int i = 0; i < 20; i++)
            {
                cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                count++;
            }
            break;
        }
        case(KB_LEFT):
        {
            count -= 40;
            if (count < 0)
            {
                count = 4000;
                for (int i = 0; i < 20; i++)
                {
                    --count;
                    cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                }
                break;
            }
            for (int i = 0; i < 20; i++)
            {
                cout << count + 1 << "\t" << arr[count]->name << "\t" << arr[count]->job << "\t" << arr[count]->dep_number << "\t" << arr[count]->date << endl;
                count++;
            }
            break;
        }
        case(KB_DOWN):
        {
            for (int i = 0; i < 4000; i++)
            {
                cout << i + 1 << "\t" << arr[i]->name << "\t" << arr[i]->job << "\t" << arr[i]->dep_number << "\t" << arr[i]->date << endl;
            }
            break;
        }
        default:

            break;
        }
    }

}

void HeapSort_bd(Enterprise** array_pointer)
{
    int L = N / 2;
    while (L > 0)
    {
        Create_New_Heap(array_pointer, array_pointer[L - 1], L, N - 1);
        L--;
    }
    int R = N - 1;
    while (R > 0)
    {
        swap(array_pointer[0], array_pointer[R]);
        R--;
        Create_New_Heap(array_pointer, array_pointer[L], L + 1, R);
    }
}

void Create_New_Heap(Enterprise** array_pointer, Enterprise* key, int L, int R)
{
    bool flag = 1;
    int i = L - 1;
    while (flag == 1)
    {
        int j = (2 * i) + 1;
        if (j > R) {
            break;
        }
        if (j < R && (compression(array_pointer[j + 1], array_pointer[j]) == 1)) {
            j++;
        }
        if (compression(key, array_pointer[j]) == 1) {
            break;
        }
        array_pointer[i] = array_pointer[j];
        i = j;
    }
    array_pointer[i] = key;
}

int Split_to_int(const char* str, char separator)
{
    int tokens[3];
    stringstream ss(str);
    string buff;
    int i = 0;

    while (getline(ss, buff, ' '))
    {
        int temp = stoi(buff);
        tokens[i] = temp;
        ++i;
    }

    return tokens[0];
}

int compression(Enterprise* left_p, Enterprise* right_p)
{
    int left_key = Split_to_int(left_p->date, '-');
    int right_key = Split_to_int(right_p->date, '-');

    if (left_key > right_key) {
        return 1;
    }
    else if (left_key < right_key) {
        return 0;
    }
    else
    {
        if (strcmp(left_p->name, right_p->name) > 0) {
            return 1;
        }
        else return 0;
    }
}

int bin_search(Enterprise** arr, int& key)
{
    for (int i = 0; i < 10; i++)
    {
        if (Split_to_int(arr[i]->date, ' ') > Split_to_int(arr[i + 1]->date, ' ')) {
            HeapSort_bd(arr);
            break;
        }
    }

    int mid;
    int L = 0;
    int R = N - 1;
    bool flag = false;
    while (L < R)
    {
        mid = Split_to_int(arr[(L + R) / 2]->date, ' ');

        if (mid < key) L = ((L + R) / 2) + 1;
        else {
            R = (L + R) / 2;
        }
    }
    if (Split_to_int(arr[L]->date, ' ') == key) {
        return L;
    }
    else {
        int temp;
        cout << "key didn't found" << endl;
        cout << "enter a new day of birth" << endl;
        cin >> temp;
        key = temp;
        system("CLS");
        return bin_search(arr, key);
    }
}

queue create_queue(Enterprise** arr, int index, int key)
{
    queue* queue_t = new queue;
    spis* current_spis = new spis(*arr[index]);
    queue_t->head = current_spis;

    ++index;
    while ((index < N) && (Split_to_int(arr[index]->date, '-') == key))
    {
        spis* temp = new spis(*arr[index]);
        current_spis->next = temp;
        current_spis = temp;
        ++index;
    }
    queue_t->tail = current_spis;
    return *queue_t;
}

void print_queue(queue* head)
{
    int KB_code = 0;
    while (KB_code != KB_ESCAPE)
    {
        spis* temp = head->head;
        while (temp != NULL)
        {
            cout << temp->data.name << "\t" << temp->data.job << "\t" << temp->data.dep_number << "\t" << temp->data.date << endl;
            temp = temp->next;
        }

        cout << "\nTo exit press Esc" << endl;
        KB_code = _getch();
        system("CLS");
    }
}

void create_tree(B2_Tree*& root, queue* queue_t)
{
    int VR = 1;
    int HR = 1;
    spis* temp = queue_t->head;
    while (temp != NULL)
    {
        B2_insert(temp->data, root, VR, HR);
        temp = temp->next;
    }
    delete temp;
}

void B2_insert(Enterprise data, B2_Tree*& p, int& VR, int& HR)
{
    if (p == NULL)
    {
        p = new B2_Tree;
        p->data = data;
        p->left = p->right = NULL;
        p->bal = 0;
        VR = 1;
    }
    else if (data.dep_number < p->data.dep_number)
    {

        B2_insert(data, p->left, VR, HR);
        if (VR == 1)
        {
            if (p->bal == 0) 
            {
                B2_Tree* q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                q->bal = 1;
                HR = 1;
                VR = 0;
            }
            else {
                p->bal = 0;
                VR = 1;
                HR = 0;
            }
        }
        else {
            HR = 0;
        }
    }
    else if (data.dep_number > p->data.dep_number)
    {
        B2_insert(data, p->right, VR, HR);
        if (VR == 1)
        {
            p->bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1)
        {
            if (p->bal == 1)
            {
                B2_Tree* q = p->right;
                p->bal = 0;
                q->bal = 0;
                p->right = q->left;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
        }
    }
    else if (p->data.dep_number == data.dep_number) {
        spis* temp = p->equal_items;
        spis* current = new spis(data);
        p->equal_items = current;
        p->equal_items->next = temp;
    }
}

B2_Tree* tree_search(unsigned short int searchKey, B2_Tree* head) {
    B2_Tree* current = head;
    while (current != nullptr) {
        if (searchKey < current->data.dep_number) {
            current = current->left;
        }
        else if (searchKey > current->data.dep_number) {
            current = current->right;
        }
        else {
            return current; 
        }
    }
    return NULL;

}

void print_tree(B2_Tree*& root)
{
    if (root != NULL) {
        print_tree(root->left);
        cout << root->data.name << "\t" << root->data.job << "\t" << root->data.dep_number << "\t" << root->data.date << endl;
        if (root->equal_items != NULL)
        {
            spis* temp = root->equal_items;
            while (temp != NULL)
            {
                cout << temp->data.name << "\t" << temp->data.job << "\t" << temp->data.dep_number << "\t" << temp->data.date << endl;
                temp = temp->next;
            }
        }
        print_tree(root->right);
    }
}

double cmp(code_huf a, code_huf b) {
    return a.probabilitie > b.probabilitie;
}

void Huffman_code(Enterprise** arr) {
    system("chcp 1251");
    system("CLS");
    vector<code_huf> alf;

    FILE* stream;
    fopen_s(&stream, "obj/testBase2.dat", "r");
    if (stream == NULL) {
        cout << "file didn't open";
        exit(1);
    }
    while (!feof(stream)) {
        char curr = getc(stream);
        code_huf* temp = new code_huf(curr);
        bool search = 0;
        for (auto &it : alf) {
            if (it.letter == curr) {
                search = 1;
                ++(it.frequence);
            }
        }
        if (search == 0) {
            alf.push_back(*temp);
        }
        
    }
    fclose(stream);
    alf.pop_back();

    const int size = alf.size();
    int sum = 0;

    for (auto &it : alf) {
        sum += it.frequence;
    }

    for (auto &it : alf) {
        it.probabilitie = it.frequence / (double)sum;
    }

    double entr = 0;
    for (auto &it : alf) {
        entr += it.probabilitie * log2(it.probabilitie);
    }
    entr = -entr;

    sort(alf.begin(), alf.end(), cmp);

    int** code = new int* [size];
    for (int i = 0; i < size; i++)
        code[i] = new int[size];
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            code[i][j] = 0;

    Huffman(alf,code, size-1);
    
    double avr_len = 0;
    for (auto &it : alf) {
        avr_len += it.code_len * it.probabilitie;
    }

    cout << "|letter|\t|code_len|\t|probabilitie|\t|code|" << endl;
    for (int i = 0; i < size; i++) {
        cout << "|" << alf[i].letter << "|\t\t|" << alf[i].code_len << "|\t\t|" << alf[i].probabilitie << "|\t|";

        for (int j = 0; j < alf[i].code_len; j++) {
            cout << code[i][j];
        }cout << "|\n";
    }

    cout << "Entropy: " << entr << "\nHuffman: " << avr_len << endl;
    double compression = CodeBase(alf, code);
    cout << "compression = " << compression << endl;
}

void Huffman(vector<code_huf> &alf, int** code, int n) {
    if (n == 1)
    {
        code[0][0] = 0;
        code[1][0] = 1;
        alf[0].code_len = alf[1].code_len = 1;
    }
    else
    {
        double q = alf[n - 1].probabilitie + alf[n].probabilitie;
        int j = Up(alf, code, n, q);
        Huffman(alf, code, n-1);
        Down(alf, code, n, j);
    }
}

int Up(vector<code_huf>& alf, int** code, int n, double q) {
    int j = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (alf[i].probabilitie <= q) {
            alf[i + 1].probabilitie = alf[i].probabilitie;
        }
        else {
            j = i;
            break;
        }
    }
    alf[j].probabilitie = q;
    return j;
}


void Down(vector<code_huf>& alf, int** code, int n, int j) {
    int M = alf.size();
    int* S = new int[M];
    for (int i = 0; i < M; i++)
        S[i] = code[j][i];
    int L = alf[j].code_len;
    for (int i = j; i < n - 2; i++) {
        for (int k = 0; k < M; k++)
            code[i][k] = code[i + 1][k];
        alf[i].code_len = alf[i + 1].code_len;
    }
    for (int i = 0; i < M; i++) {
        code[n - 2][i] = S[i];
        code[n - 1][i] = S[i];
    }
    code[n - 2][L + 1] = 0;
    code[n - 1][L + 1] = 1;
    alf[n - 1].code_len = alf[n].code_len = L + 1;
}

double CodeBase(vector<code_huf>& alf, int** code) {
    cout << "Coding..." << endl;

    ifstream f("obj/testBase2.dat", ios::binary);
    ofstream fcoded ("obj/BaseCoded.dat");
    int f_compression = 0;
    int fcoded_compression = 0;
    if (f.is_open() && fcoded.is_open())
    {
        char buffer;
        int size = alf.size();
        while (!f.eof())
        {
            f >> buffer;
            ++f_compression;
            for (int i = 0; i < size; i++) {
                if (buffer == alf[i].letter) {
                    for (int j = 0; j < alf[i].code_len; j++) {
                        fcoded << code[i][j];
                        ++fcoded_compression;
                    }
                }
            }
        }

        f.close();
        fcoded.close();
        cout << "File has been coded" << endl;
    }
    else
    {
        cout << "Error opening file!" << endl;
        exit(-1);
    }
    
    return fcoded_compression / (double)f_compression;
}
