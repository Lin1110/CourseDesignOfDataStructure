#include "mainwindow.h"
#include "./ui_mainwindow.h"

int N = 26+26+3+1;


TreeNode build(int w[],char v[]);
void CrtHuffmanCode1(TreeNode ht,char** hc,int n);
void CodeToChar(TreeNode ht,char* chars,ofstream &out);
void CharToCode(char* chars,char** hc, char* str,ofstream &out);
int getFileName(const char* path,char** Name);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    ui->pushButton_3->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    memset(str,0,sizeof(char)*100);
    memset(w,0,sizeof(int)*100);
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("choose file");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setDirectory("/home/lyj/CLionProjects/data");
    fileDialog->setNameFilter(tr("Souce Files(*.souce.*[0-9] *.souce)"));
    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        ui->label->setText(path);
    }
    char StrLine[1024];
    QByteArray ba=(ui->label->text()).toLatin1();
    FILE *fp=fopen(ba.data(),"rb");
    if(fp == NULL){
//        exit(-1);
        ui->label->setText("NO CHOOSE FILE");
        return;
    }
    while (!feof(fp)) {
//        printf("OK");
        int k = 0;
        fgets(StrLine, 1024, fp);  //读取一行
        while (StrLine[k] != '\n' && StrLine[k] != '\0') {
            int i=0;
            for (i=0; str[i]!='\0'; i++) {
                if (str[i] == StrLine[k]){
                    break;
                }
            }
            if (str[i]=='\0'){
                str[i] = StrLine[k];
            }
            k++;
        }
    }
    fclose(fp);
    puts(str);

    path_tag=ba.data();
    cout << path_tag << endl;
    fp=fopen(ba.data(),"rb");
    if(fp == NULL){
//        exit(-1);
        ui->label->setText("NO CHOOSE FILE");
        return;
    }
    while (!feof(fp)) {
        int k = 0;
        fgets(StrLine, 1024, fp);  //读取一行
        puts(StrLine);
        while (StrLine[k] != '\n' && StrLine[k] != '\0') {
            int i=0;
            for (i=0; str[i]!='\0'; i++) {
                if (str[i] == StrLine[k]){
                    w[i]++;
                }
            }
            k++;
        }
    }
    fclose(fp);
    for (int i=0;i<3;i++) {
        printf("%d",w[i]);
    }
    for (int j = 0; str[j]!='\0' ; j++) {
        N=j+1;/////////////////////////////////////////////////////////////////////////警告
    }
    ui->pushButton_3->setEnabled(true);
    QString qstring("BUILD OK!");
    ui->label_5->setText(qstring);
//    textEdit
    TreeNode table = build(w, str);
    string str_tree("");

    for(int j=0; j<2*N-1; j++){
        str_tree += to_string(table[j].father) + " " +
                to_string(table[j].Lchild) + " " +
                to_string(table[j].Rchild) + " " +
                to_string(table[j].weight) + " " +
                (char)table[j].val + " " +
                "\n";
    }
    QString qstring_tree(str_tree.c_str());
    ui->textEdit->setText(qstring_tree);
}

void MainWindow::on_pushButton_2_clicked()
{

    TreeNode table = build(w, str);
//    for(int j=0; j<2*N-1; j++){
//        printf("%d %d %d %d %c\n",
//               table[j].father,
//               table[j].Lchild,
//               table[j].Rchild,
//               table[j].weight,
//               table[j].val
//        );
//    }

    char** hc = (char**)malloc(sizeof(char*)*N);
    CrtHuffmanCode1(table,hc,N);
    string string_cs("");
    for(int j=0; j<N; j++){
        string_cs += table[j].val;
        string_cs += ":";
        string_cs += hc[j];
        string_cs += "\n";
//    printf("%c:%s\n",
//            table[j].val,
//            hc[j]
//           );
    }
    QString qstring_tree(string_cs.c_str());
    ui->textEdit->setText(qstring_tree);
    fstream infile;
    basic_ofstream<char> outfile;
    QByteArray ba=(ui->label->text()).toLatin1();
    infile.open(ba.data(), ios::in);

    char* Name = NULL;
    getFileName(ba.data(),&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = string_1 + Name + ".code";


//    cout << path_tag << endl;
//    string string("/home/lyj/CLionProjects/data/");

    outfile.open(string_1, ios::out);
    if (!infile)
    {
        cout << "can't open 1!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open 2!" + string_1<< endl;
        abort();
    }
    char ch[1024] = {0};
    while (!infile.eof())
    {
        infile.getline(ch, 1024);
        CharToCode(ch,hc,str,outfile);
        outfile << "\n";
        cout << "\n";
    }
    cout << endl;
    infile.close();
    outfile.close();

    string_1 = "Code OK\nSave As:" + string_1;
    QString qstring=QString(QLatin1String(string_1.c_str()));
    ui->label_5->setText(qstring);
}

void MainWindow::on_pushButton_3_clicked()
{
    TreeNode table = build(w, str);
    fstream infile;
    basic_ofstream<char> outfile;
    QByteArray ba=(ui->label_2->text()).toLatin1();
    infile.open(ba.data(), ios::in);

    char* Name = NULL;
    getFileName(ba.data(),&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = string_1 + Name + ".encode";

    outfile.open(string_1, ios::out);
    if (!infile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    char chars[1024*5] = {0};
    while (!infile.eof())
    {
        infile.getline(chars, 1024*5);
//        puts(chars);
        CodeToChar(table, chars, outfile);
        outfile << "\n";
        cout << "\n";
    }
    cout << endl;
    infile.close();
    outfile.close();

    string_1 = "Encode OK\nSave As:" + string_1;
    QString qstring=QString(QLatin1String(string_1.c_str()));
    ui->label_5->setText(qstring);

}

int getFileName(const char* path,char** Name){
    *Name = (char*) malloc(sizeof(char)*20);
    for (int i = 0,j=0; path[i]!='/0' ; i++,j++) {
        if(path[i] == '/'){
//            putchar('0');
            j=-1;
            continue;
        } else if(path[i] == '.'){
            (*Name)[j] = '\0';
//            putchar('1');
            return 1;
        } else {
            (*Name)[j] = path[i];
//            printf(" %d%c ",j,(*Name)[j]);
//            putchar(path[i]);
        }
    }
    free(*Name);
    *Name = NULL;
    return 0;
}

int* select(TreeNode table, int num){
    int nums[2];
    int* set = (int*)malloc(sizeof(int)*2);
    int j=0;int i;
    for(i=0; i<num; i++){
        if(j == 2) break;
        if(table[i].father != -1) continue;
        else{
            nums[j] = table[i].weight;
            set[j] = i;
            j++;
        }
    }
//  printf("%d %d**********\n\n\n",set[0],set[1]);
    int x=nums[0],y=set[0];
    nums[0] = x>nums[1]?nums[1]:x;
    set[0] = x>nums[1]?set[1]:y;
    set[1] = x>nums[1]?y:set[1];
    nums[1] = x>nums[1]?x:nums[1];

//  printf("%d %d**********\n\n\n",set[0],set[1]);
    for(i=0; i<num-1; i++) {
        if(table[i].father != -1) continue;
        else{
            if(nums[1]>table[i].weight&&i!=set[0]){
                x=nums[0],y=set[0];
                nums[0] = table[i].weight>x?x:table[i].weight;
                set[0] = table[i].weight>x?y:i;
                nums[1] = table[i].weight>x?table[i].weight:x;
                set[1] = table[i].weight>x?i:y;
            }
        }
    }
//  int _tag_set = set[0];
//  set[0] = set[1];
//  set[1] = _tag_set;
//  printf("%d %d**********\n\n\n",set[0],set[1]);
    return set;
}

TreeNode build(int w[],char v[]){
    int n = N;
    TreeNode table = (TreeNode)malloc(sizeof(Tree)*(2*n-1));
    int i=0;
    for(i=0; i<(2*n-1); i++){
        table[i].father = -1;
        table[i].Lchild = -1;
        table[i].Rchild = -1;
        table[i].val = '!';
        table[i].weight = 0;
    }
    for(i=0; i<n; i++) {
        table[i].weight = w[i];
        table[i].val = v[i];
    }
    int j;
    for(i=n; i<2*n-1; i++) {

        int* arr = select(table,i);
        int x = arr[0],y = arr[1];
        table[i].weight = table[x].weight+table[y].weight;
        table[i].Lchild = x;
        table[i].Rchild = y;
        table[x].father = i;
        table[y].father = i;
    }
    return table;
}

void CrtHuffmanCode1(TreeNode ht,char** hc,int n){
    for(int j=0; j<2*N-1; j++){
        printf("%d %d %d %d %c\n",
               ht[j].father,
               ht[j].Lchild,
               ht[j].Rchild,
               ht[j].weight,
               ht[j].val
        );
    }
    char* cd=(char*)malloc(2*n*sizeof(char));
    memset(cd,0, sizeof(char)*2*n);
    int start;
    cd[n-1] = '\0';
    int i=0,c=0,p=0;
    for(i=0;i<n;i++){
        start=n;
        c=i;
        p=ht[i].father;
        while (p!=-1){
            start--;
//          printf("%d %d**********\n\n\n",ht[p].Lchild,c);
            if(ht[p].Lchild==c) cd[start]='0';
            else cd[start]= '1';
            c=p;
            p=ht[p].father;
        }

        hc[i] = (char*)malloc((n-start)*sizeof (char));
//        memset(hc[i],'\0', sizeof(char)*(n-start));
        strcpy(hc[i], &cd[start]);
//        puts(hc[i]);
        printf("%c:%s\n",ht[i].val,hc[i]);
    }
    free(cd);
}

void CodeToChar(TreeNode ht,char* chars,ofstream &out){
//    printf("%d\n",N);
//    for(int j=0; j<2*N-1; j++){
//        printf("%d %d %d %d %c\n",
//               ht[j].father,
//               ht[j].Lchild,
//               ht[j].Rchild,
//               ht[j].weight,
//               ht[j].val
//        );
//    }
    int i=0;
    TreeNode p = ht+2*N-2;
    while(*chars != '\0'){
//        putchar(*chars);
        if(p->val!='!'){
            out << (*p).val;
            printf("%c",(*p).val);
            p = ht+2*N-2;
        }
        if(*chars == '0'){
            p = ht+(*p).Lchild;
        }else{
            p = ht+(*p).Rchild;
        }
        chars++;
    }
    if((*p).val!='!'){
        out << (*p).val;
        printf("%c",(*p).val);
    }
}

void CharToCode(char* chars,char** hc, char* str,ofstream &out){
    while(*chars != '\0'){
        for (int i = 0; i < N; i++) {
            if (*chars == str[i]){
                out << *(hc+i);
                printf("%s",*(hc+i));
                break;
            }
        }
        chars++;
    }
}

int zip(char* path){
    char* Name = NULL;
    getFileName(path,&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = string_1 + Name + ".code.zip_hfmTree";
    fstream infile,outfile;
    infile.open(path, ios::in);
    outfile.open(string_1, ios::out|ios::binary);
    if (!infile)
    {
        cout << "can't open infile!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open outfile!" << endl;
        abort();
    }
    char ch[1024*5] = {0};
    while (!infile.eof())
    {
        infile.getline(ch, 1024*5);
//        cout << ch;
//        cout << "\n";
        unsigned char save_bit = {0};
        int count=0;
        for (int i=0;ch[i] != '\0';i++){
            count++;
        }
//        cout << (int)count<<endl;
        int count_8 = count/8 + ((count%8)?1:0);
        outfile.write((char*)&count, sizeof(int));
        int i=0;
        int num =0;
        for (i=0;ch[i] != '\0';i++){
            if(ch[i] == '1'){
                save_bit += 1<<(i%8);
            }
            if(i%8 == 7){
                outfile << save_bit;
//                cout << save_bit;
                save_bit = 0;
                num++;
            }
        }
        if(num<count_8){
            outfile << save_bit;
        }


//        cout << (int)num<<endl;
//        outfile << "\n";
//        cout << "\n";
    }
    cout << endl;
    infile.close();
    outfile.close();
    return 1;
}

int unzip(char* path){
    char* Name = NULL;
    getFileName(path,&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = string_1 + Name + ".code.unzip_hfmTree";
//    puts(string_1.c_str());
    fstream infile,outfile;
    infile.open(path, ios::in);
    outfile.open(string_1, ios::out);
    if (!infile)
    {
        cout << "can't open infile!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open outfile!" << endl;
        abort();
    }
    char ch[1024*5] = {0};
//    for (int i = 0; i <1024*5 ; i++) {
//        ch[i] =
//    }
    while (!infile.eof())
    {
        int count = 0;
        infile.read((char*)&count, sizeof(int));
        if(count == 0){
            continue;
        }
        int count_8 = count/8 + ((count%8)?1:0);
//        int count_8 = count/8;
        infile.read((char*)ch, sizeof(char)*(count_8));
//        cout << (int)count_8<<endl;
//        cout << (int)count<<endl;
//        infile.getline(ch, 1024*5);
//        unsigned char save_bit = 0;
        int num = 0;
        for (int i=0;i<count_8;i++){
            for (int j = 0; j < 8; j++) {
                num++;
                if (i*8+j == count){
                    break;
                }
                outfile << (unsigned int)(( (unsigned)ch[i] & ((unsigned)1<<j) ) >>j);
//                cout << (unsigned int)(( (unsigned)ch[i] & ((unsigned)1<<j) ) >>j);
            }
        }

//        cout << ch;
        outfile << "\n";
//        cout << "\n";
//        cout << (int)num<<endl;
    }
//    cout << endl;
    infile.close();
    outfile.close();
}

int main_(void){
//    int weight_Small[26] = {0};
//    int weight_Big[26] = {0};
//    int weight_S[3] = {0};
////    printf("%d,%d,%d,%d",'a',122-97+1,'A','Z');
//    char StrLine[1024];
//    int i=0;
//    int _n = 0;
//    FILE *fp=fopen("test.souce","rb");
//    if(fp == NULL){
//        exit(-1);
//    }
//    while (!feof(fp))
//    {
//        int k=0;
//        fgets(StrLine,1024,fp);  //读取一行
//        while (StrLine[k] != '\n' && StrLine[k] != '\0'){
//            if ((int)StrLine[k]<=122&&(int)StrLine[k]>=97){
//                weight_Small[(int)StrLine[k]-97] ++;
//            } else if ((int)StrLine[k]<=90&&(int)StrLine[k]>=65){
//                weight_Big[(int)StrLine[k]-65] ++;
//            } else {
//                switch ((int)StrLine[k]){
//                    case ' ':
//                        weight_S[0]++;
//                        break;
//                    case ',':
//                        weight_S[1]++;
//                        break;
//                    case '.':
//                        weight_S[2]++;
//                        break;
//                    case '?':
//                        _n++;
//                        break;
//                    default:
//                        ;
//                }
//            }
//            k++;
//        }
//        i++;
//    }
////    printf("%d\n", weight_Big[0]); //输出
//    fclose(fp);
//    printf("%d\n",i);
//    ////////////////////////////////////////////////
//    char str[N+1] = {0};
//    for (int j = 97; j <= 122; j++) {
//        str[j-97] = j;
//    }
//    for (int j = 65+26; j <=90+26 ; j++) {
//        str[j-65] = j-26;
//    }
//    str[26+26+0] = ' ';
//    str[26+26+1] = ',';
//    str[26+26+2] = '.';
//    str[26+26+3] = '?';
//    str[26+26+4] = '\0';
//    puts(str);
//    //////////////////////////////////////////
//    int w[N] = {0};
//    for (int j = 97; j <= 122; j++) {
//        w[j-97] = weight_Small[j-97];
//    }
//    for (int j = 65+26; j <=90+26 ; j++) {
//        w[j-65] = weight_Big[j-26-65];
//    }
//    w[26+26+0] = weight_S[0];
//    w[26+26+1] = weight_S[1];
//    w[26+26+2] = weight_S[2];
//    w[26+26+3] = _n;
//    //////////////////////////////////////////////////
//
   //
     //

    char str[100] = {0};
    int w[100] = {0};
    char StrLine[1024];
    FILE *fp=fopen("test.souce","rb");
    if(fp == NULL){
        exit(-1);
    }
    while (!feof(fp)) {
//        printf("OK");
        int k = 0;
        fgets(StrLine, 1024, fp);  //读取一行
        while (StrLine[k] != '\n' && StrLine[k] != '\0') {
            int i=0;
            for (i=0; str[i]!='\0'; i++) {
                if (str[i] == StrLine[k]){
                    break;
                }
            }
            if (str[i]=='\0'){
                str[i] = StrLine[k];
            }
            k++;
        }
    }
    fclose(fp);
    puts(str);
    fp=fopen("test.souce","rb");
    if(fp == NULL){
        exit(-1);
    }
    while (!feof(fp)) {
        int k = 0;
        fgets(StrLine, 1024, fp);  //读取一行
        while (StrLine[k] != '\n' && StrLine[k] != '\0') {
            int i=0;
            for (i=0; str[i]!='\0'; i++) {
                if (str[i] == StrLine[k]){
                    w[i]++;
                }
            }
            k++;
        }
    }
    fclose(fp);
    for (int j = 0; str[j]!='\0' ; j++) {
        N=j+1;/////////////////////////////////////////////////////////////////////////警告、、、、、、、
    }

     //
   //
//
    TreeNode table = build(w, str);
    char** hc = (char**)malloc(sizeof(char*)*N);
    CrtHuffmanCode1(table,hc,N);
//    for(int j=0; j<N; j++){
//    printf("%c:%s\n",
//            table[j].val,
//            hc[j]
//    );
//    }
    fstream infile;
    basic_ofstream<char> outfile;
    infile.open("test.souce", ios::in);
    outfile.open("test.code", ios::out);
    if (!infile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    char ch[1024] = {0};
    while (!infile.eof())
    {
        infile.getline(ch, 1024);
        CharToCode(ch,hc,str,outfile);
        outfile << "\n";
        cout << "\n";
    }
    cout << endl;
    infile.close();
    outfile.close();

    infile.open("test.code", ios::in);
    outfile.open("test.encode", ios::out);
    if (!infile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    if (!outfile)
    {
        cout << "can't open!" << endl;
        abort();
    }
    char chars[1024*5] = {0};
    while (!infile.eof())
    {
        infile.getline(chars, 1024*5);
//        puts(chars);
        CodeToChar(table, chars, outfile);
        outfile << "\n";
        cout << "\n";
    }
    cout << endl;
    infile.close();
    outfile.close();

//    zip();
//    unzip();
    return 0;
}

void MainWindow::on_pushButton_5_clicked()
{
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("choose file");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setDirectory("/home/lyj/CLionProjects/data");
    fileDialog->setNameFilter(tr("Code Files(*.code *.code.unzip_hfmTree)"));
    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        ui->label_2->setText(path);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("choose file");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setDirectory("/home/lyj/CLionProjects/data");
    fileDialog->setNameFilter(tr("Code Files(*.code)"));
    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        ui->label_3->setText(path);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QByteArray ba=(ui->label_3->text()).toLatin1();
    zip(ba.data());

    char* Name = NULL;
    getFileName(ba.data(),&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = "zip OK\nSave As:" + string_1 + Name + ".code.zip_hfmTree";
    QString qstring=QString(QLatin1String(string_1.c_str()));
    ui->label_5->setText(qstring);

//    QString qstring=QString(QLatin1String("zip OK\n"));
//    ui->label_5->setText(qstring);
}


void MainWindow::on_pushButton_7_clicked()
{
    //	QString fileName = QFileDialog::getOpenFileName(
    //		this,
    //		tr("open a file."),
    //		"D:/",
    //		tr("images(*.png *jpeg *bmp);;video files(*.avi *.mp4 *.wmv);;All files(*.*)"));
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle("choose file");
    fileDialog->setFileMode(QFileDialog::AnyFile);
    fileDialog->setDirectory("/home/lyj/CLionProjects/data");
////    fileDialog->setFilter()
//    fileDialog->filter();
    fileDialog->setNameFilter(tr("ZIP_H Files(*.code.zip_hfmTree)"));
    if(fileDialog->exec()==QDialog::Accepted){
        QString path=fileDialog->selectedFiles()[0];
        ui->label_4->setText(path);
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    QByteArray ba=(ui->label_4->text()).toLatin1();
    unzip(ba.data());
//    QString qstring("hello");
    char* Name = NULL;
    getFileName(ba.data(),&Name);
    string string_1("/home/lyj/CLionProjects/data/");
    string_1 = "unzip OK\nSave As:" + string_1 + Name + ".code.unzip_hfmTree";
    QString qstring=QString(QLatin1String(string_1.c_str()));
    ui->label_5->setText(qstring);
}
