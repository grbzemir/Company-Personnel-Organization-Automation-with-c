#include<stdio.h>   
#include<stdlib.h>
#include<string.h>
#include<stddef.h>


typedef struct Bolum 
{
    int bolumID;
    char bolumAd[20];
    int personelSayisi;

} bolum;

typedef struct Kisisel 
{
    char dogumTarih[10];
    char dogumYeri[20];
    char cinsiyet[10];
    char medeniHali[10];

} kisisel;

typedef struct Iletisim
{
   
   char sehir[20];
   char ilce[20];
   char adres[50];
   char tel[20];
   char eposta[30];

} iletisim;

typedef struct Personel

{

  int bolumID;
  char TC[11];
  char adSoyad[30];
  char baslamaTarihi[10];
  float maas;
  kisisel k1;
  iletisim i1;


} personel;


void bolumEkle()
{
    
  system("cls");
  printf("\tBOLUM EKLEME\n\n");
  bolum b1;

  int numara;
  numara=0;

  FILE *numPtr = fopen("bolumNumaralar.dat","a+b");
  while(fread(&numara,sizeof(int),1,numPtr)!=NULL)

  {
     
  }

     numara++;
     fwrite(&numara, sizeof(int),1,numPtr);
     fclose(numPtr);


     b1.bolumID=numara;
     printf("Bolum Adi:");
     scanf("%s",b1.bolumAd);
     b1.personelSayisi=0;
    

    FILE *ptr = fopen("bolumler.dat","a+b");
    fwrite(&b1, sizeof(bolum),1,ptr);
    fclose(ptr);
    printf("Bolum kaydi tamamdir...\n");


}

void bolumListele()
{

    system("cls");
    printf("Bolum listesi...\n\n");
    bolum b1;

    printf("%-20s%-20s%-20s\n","Bolum ID","Bolum Ad","Personel Sayisi");
    FILE *ptr = fopen("bolumler.dat","r+b");
    while(fread(&b1, sizeof(bolum),1,ptr)!= NULL)

    {
        printf("%-20d%-20s%-20d\n",b1.bolumID,b1.bolumAd,b1.personelSayisi);
    }
    
    fclose(ptr);

}



void bolumDuzenle()
{


    system("cls");
    printf("\tBOLUM DUZENLEME\n\n");
    bolum b1;
    int numara;
    int sonuc=0;
    int sayac=0;
    bolumListele();
    printf("Bolum No:");
    scanf("%d",&numara);

    FILE *ptr=fopen("bolumler.dat","r+b");

    while(fread(&b1, sizeof(bolum),1,ptr)!= NULL)

    {
        if(b1.bolumID==numara)
        {
           printf("%-20s%-20s%-20s\n","Bolum ID","Bolum Adi","Personel Sayisi");
           printf("%-20d%-20s%-20d\n",b1.bolumID,b1.bolumAd,b1.personelSayisi);
           sonuc=1;
           break;

        }
        
        sayac++;

    }

    if(sonuc==0)
    printf("%d numarali bolum bulunamadi \n",numara);
    else
    {
        rewind(ptr);
        printf("Bolum Yeni Adi:");
        scanf("%s",b1.bolumAd);

        fseek(ptr,sayac*sizeof(bolum),SEEK_SET);
        fwrite(&b1, sizeof(bolum),1,ptr);
        printf("Bolum adi degistirildi...\n");
          
    }

    fclose(ptr);

}

void bolumSil()
{
   
    system("cls");
    printf("\tBOLUM SILME\n\n");
    bolum b1;
    bolumListele();
    int numara;
    int sonuc=0;

    printf("Bolum No:");
    scanf("%d",&numara);
    
    printf("%-20s%-20s%-20s\n","Bolum ID","Bolum Adi","Personel Sayisi");
    FILE *ptr=fopen("bolumler.dat","r+b");
    while(fread(&b1, sizeof(bolum),1,ptr)!= NULL)

    {
        if(b1.bolumID==numara )
        {
           
           sonuc=1;
           break;

        }
        
    }
     
    
    if(sonuc==0)

    {
    
    fclose(ptr);
    printf("%d numarali bolum bulunamadi \n",numara);
    
    }

    else if(b1.personelSayisi !=0)
    {
        fclose(ptr);
        printf("Bu bolumde personel var silinemez...\n",numara);

    }

    else
    {
        rewind(ptr);
        FILE *yptr=fopen("yedek.dat","a+b");
        while(fread(&b1, sizeof(bolum),1,ptr)!= NULL)

        {

            if(b1.bolumID!=numara)

            {

                fwrite(&b1, sizeof(bolum),1,yptr);
                
            }
        }
       
       fclose(yptr);
       fclose(ptr);
        
         remove("bolumler.dat"); // silme islemi
         rename("yedek.dat","bolumler.dat"); // degistirme islemi
         printf("Bolum silindi...\n");

    }

    fclose(ptr);





}



int  bolumMenu()
{   

    int secim;

    printf("\n\tBOLUM ISLEMLERI\n\n");
    printf("\t1-Bolum Ekle\n\n");
    printf("\t2-Bolum Duzenle\n\n");
    printf("\t3-Bolum Sil\n\n");
    printf("\t4--Bolum Listele\n\n");
    printf("\t0-CIKIS\n\n");
    printf("\tSeciminiz:");
    scanf("%d",&secim);

    system("cls");

    return secim;

}

void bolumIslemleri()
{
  
  int secim;
  secim=bolumMenu();

  while(secim!=0)
  {
    switch(secim)

  {

    case 1:
    bolumEkle();
    break;

    case 2:
    bolumDuzenle();
    break;

    case 3:
    bolumSil();
    break;

    case 4:
    bolumListele();
    break;

    case 0:
    break;

    default:
    printf("Yanlis secim yaptiniz");

  }

  secim=bolumMenu();

  }

printf("cikis yaptiniz...");


}


void bolumGuncelle(int numara , int sayi)
{
  
    FILE *ptr=fopen("bolumler.dat","r+b");
    bolum b1;
    int sayac=0;
    while(fread(&b1, sizeof(bolum),1,ptr)!= NULL)

    {
        if(b1.bolumID==numara)
        {
          
           break;

        }

        sayac++;
        
    }

    rewind(ptr); // poniter basa dönsün !
    fseek(ptr,sayac*sizeof(bolum),SEEK_SET);
    b1.personelSayisi=b1.personelSayisi+sayi;
    fwrite(&b1, sizeof(bolum),1,ptr);
    fclose(ptr);
    printf("Bolum guncellendi...\n");

}



void personelEkle()
{


  system("cls");  
  printf("\tPERSONEL EKLEME\n\n");
  personel p1;

  
    printf("TC :");
    scanf("%s",p1.TC);
    printf("Ad Soyad :");
    scanf("%s",p1.adSoyad);
    bolumListele();
    printf("Bolum  No:");
    scanf("%d",&p1.bolumID);
    printf("Ise baslama tarihi:");
    scanf("%d",&p1.baslamaTarihi);
    printf("Maas:");
    scanf("%d",&p1.maas);

    system("cls");
    printf("Kisiel Bilgiler\n\n");

    printf("Dogum Tarih:");
    scanf("%d",&p1.k1.dogumTarih);
    printf("Dogum Yeri:");
    scanf("%s",p1.k1.dogumYeri);
    printf("Cinsiyet:");
    scanf("%s",p1.k1.cinsiyet);
    printf("Medeni Hal:");
    scanf("%s",p1.k1.medeniHali);

    system("cls");
    printf("Iletisim Bilgileri\n\n");

    printf("Sehir:");
    scanf("%s",p1.i1.sehir);
    printf("Ilce:");
    scanf("%s",p1.i1.ilce);
    printf("Adres:");
    scanf("%s",p1.i1.adres);
    printf("Telefon:");
    scanf("%s",p1.i1.tel);
    printf("E-mail:");
    scanf("%s",p1.i1.eposta);

    FILE *ptr=fopen("personel.dat","a+b");
    fwrite(&p1,sizeof(personel),1,ptr);
    fclose(ptr);
    printf("Personel Kaydi tamamdir...");
    bolumGuncelle(p1.bolumID,1);


}

void personelAra()
{
  
  system("cls");
  printf("\tPERSONEL ARAMA\n\n");
  personel p1;
  
  char tc[11];
  int sonuc=0;
  printf("tc giriniz:");
  scanf("%s",tc);
  
  FILE *ptr=fopen("personel.dat","rb");
  while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

  {
    if(strcmp(tc,p1.TC)==0)

    {
        sonuc=1;
        break;
    }
  }
  
  fclose(ptr);
  if(sonuc==0)
  printf("%s TC numarali personel kaydi bulunamadi\n",tc);
  else
  {

    system("cls");
    printf("%-20s%-20s%-30s%-20s%-20s\n","TC","AD","SOYAD","BOLUM","MAAS","ISE BASLAMA TARİHİ");
    printf("%-20s%-20d%-30s%-20s%.2f\n",p1.TC,p1.adSoyad,p1.bolumID,p1.maas,p1.baslamaTarihi);

    printf("Kisisel Bilgiler\n\n");
    printf("Dogum Tarihi:%d\n",p1.k1.dogumTarih);
    printf("Dogum Yeri:%s\n",p1.k1.dogumYeri);
    printf("Cinsiyet:%c\n",p1.k1.cinsiyet);
    printf("Medeni Hal:%c\n",p1.k1.medeniHali);

    printf("Iletisim Bilgileri\n\n");
    printf("Sehir:%s\n",p1.i1.sehir);
    printf("Ilce:%s\n",p1.i1.ilce);
    printf("Adres:%s\n",p1.i1.adres);
    printf("Telefon:%s\n",p1.i1.tel);
    printf("E-mail:%s\n",p1.i1.eposta);


  }


}

void personelSil()
{


  system("cls");
  printf("\tPERSONEL SIL\n\n");
  personel p1;
  
  char tc[11];
  int sonuc=0;
  printf("tc giriniz:");
  scanf("%s",tc);
  
  FILE *ptr=fopen("personel.dat","rb");
  while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

  {
    if(strcmp(tc,p1.TC)==0)

    {
        sonuc=1;
        break;
    }
  }
  
  
  if(sonuc==0)
   {

    fclose(ptr);
    printf("%s TC numarali personel kaydi bulunamadi\n",tc);

    }


   else
   {
    
    rewind(ptr);

    system("cls");
    printf("%-20s%-20s%-30s%-20s%-20s\n","TC","AD-SOYAD","BOLUM","MAAS","ISE BASLAMA TARİHİ");
    printf("%-20s%-20d%-30s%-20s%.2f\n",p1.TC,p1.adSoyad,p1.bolumID,p1.maas,p1.baslamaTarihi);

    FILE *yPtr=fopen("yedek.dat","wb");

    char tercih;
    printf("%s numarali personeli silmek istediginize emin misiniz? (E/H)",p1.adSoyad);
    scanf("%c",&tercih);

    if(tercih=='e' && tercih=='H')
    {
        while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

        {
            if(strcmp(tc,p1.TC)!=0)
            {
                fwrite(&p1,sizeof(personel),1,yPtr);

            }
        }

        fclose(yPtr);
        fclose(ptr);
        remove("personel.dat"); // silme işlemini yapalim personel dat dosayasi silinsin
        rename("yedek.dat","personel.dat"); //yedek dat dosyasi personel dat dosyasi olacak
        printf("Silme İslemi Tamamlandi\n");
        bolumGuncelle(p1.bolumID,-1); // personeli sildigimiz icin 1 azaltiyoruz

    } 

    else
    printf("Personel silme islemi iptal edildi\n");



  }
  
  fclose(ptr);  


}

void personelListele()
{

  system("cls");
  printf("\tPERSONEL LISTELEME\n\n");
  personel p1;
  
  char tc[11];
  int numara;
  bolumListele();

  printf("Bolum No:");
  scanf("%s",numara);
  
  FILE *ptr=fopen("personel.dat","rb");
  printf("%-20s%-20s%-30s%-20s%-20s\n","TC","AD-SOYAD","BOLUM","MAAS","ISE BASLAMA TARİHİ");
  while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

  {

    if(numara==p1.bolumID)

    {
        printf("%-20s%-20d%-30s%-20s%.2f\n",p1.TC,p1.adSoyad,p1.bolumID,p1.maas,p1.baslamaTarihi);

    }
  }
  
  fclose(ptr);
 
  }


void personelMaasGuncelle()
{

  system("cls");
  printf("\tPERSONEL MAAS GUNCELLE\n\n");
  personel p1;
  
  char tc[11];
  int sonuc=0;
  int sayac=0;

  
  

  printf("TC:");
  scanf("%s",tc);
  
  FILE *ptr=fopen("personel.dat","rb");
 
  while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

  {

    if(strcmp(tc,p1.TC)==0)
    {

        sonuc=1;
        break;
    }

    sayac++;

  }

  if(sonuc=0)
  {
    
    printf("%s numarali personel kaydi bulunamadi\n",tc);
    
  }

  else
  {
        rewind(ptr);
        printf("%-20s%-20s%-30s%-20s%-20s\n","TC","AD-SOYAD","BOLUM","MAAS","ISE BASLAMA TARİHİ");
        printf("%-20s%-20d%-30s%-20s%.2f\n",p1.TC,p1.adSoyad,p1.bolumID,p1.maas,p1.baslamaTarihi);

        printf("Yeni maas giriniz:");
        scanf("%f",&p1.maas);

        fseek(ptr,sayac*sizeof(personel),0); // 0'dan basla atlayarak git
        fread(&p1,sizeof(personel),1,ptr);
        printf("Maas guncellendi\n");

  }

  fclose(ptr);
 
  

}

void personelBolumDegistir()
{

   system("cls");
   printf("\tPERSONEL BOLUM DEGISTIR\n\n");
  personel p1;
  
  char tc[11];
  int sonuc=0;
  int sayac=0;

  
  printf("TC:");
  scanf("%s",tc);
  
  FILE *ptr=fopen("personel.dat","rb");
 
  while(fread(&p1,sizeof(personel),1,ptr)!=NULL)

  {

    if(strcmp(tc,p1.TC)==0)
    {

        sonuc=1;
        break;
    }

    sayac++;

  }

  if(sonuc=0)
  {
    
    printf("%s numarali personel kaydi bulunamadi\n",tc);
    
  }

  else
  {
        rewind(ptr); // dosya basina don
        printf("%-20s%-20s%-30s%-20s%-20s\n","TC","AD","SOYAD","BOLUM","MAAS","ISE BASLAMA TARİHİ");
        printf("%-20s%-20d%-30s%-20s%.2f\n",p1.TC,p1.adSoyad,p1.bolumID,p1.maas,p1.baslamaTarihi);
        
        bolumListele();
        printf("Yeni bolum No:");
        scanf("%d",&p1.bolumID);

        int eskiBolumNo=p1.bolumID;
        bolumListele();

        printf("Yeni bolum No:");
        scanf("%d",&p1.bolumID);
        fseek(ptr,sayac*sizeof(personel),0); // 0'dan basla atlayarak git
        fread(&p1,sizeof(personel),1,ptr);
        printf("Bolum Degistirildi \n");

    
        bolumGuncelle(eskiBolumNo,-1);
        bolumGuncelle(p1.bolumID,1);

  }

  fclose(ptr);
 

}


int  personelMenu()
{   

    int secim;

    printf("\n\tPersonel ISLEMLERI\n\n");
    printf("\t1-Personel Ekle\n\n");
    printf("\t2-Personel Ara\n\n");
    printf("\t3-Personel sil\n\n");
    printf("\t4-Personel Listele\n\n");
    printf("\t5-Personel Maas Guncelle\n\n");
    printf("\t6-Personel Bolum Degistir\n\n");
    printf("\t0-CIKIS\n\n");
    printf("\tSeciminiz:");
    scanf("%d",&secim);

    system("cls");

    return secim;

}


void personelIslemleri()
{

 int secim;
  secim=personelMenu();

  while(secim!=0)
  {
    switch(secim)

  {

    case 1:
    personelEkle();
    break;

    case 2:
    personelAra();
    break;

    case 3:
    personelSil();
    break;

    case 4:
    personelListele();
    break;

    case 5:
    personelMaasGuncelle();
    break;

    case 6:
    personelBolumDegistir();
    break;

    case 0:
    break;

    default:
    printf("Yanlis secim yaptiniz");

  }

  secim=personelMenu();

  }

printf("cikis yaptiniz...");

}


int menu()
{   

    int secim;

    printf("\n\tSIRKET PERSONEL ORGANIZASYON OTOMASYONU \n\n");
    printf("\t1-BOLUM ISLEMLERI\n\n");
    printf("\t2-PERSONEL ISLEMLERI\n\n");
    printf("\t0-CIKIS\n\n");
    printf("\tSeciminiz:");
    scanf("%d",&secim);
    system("cls");
    return secim;

}


int main ()

{

  int secim;
  secim=menu();

  while(secim != 0)

  {
    
    switch(secim)
  {
    
    case 1:
    bolumIslemleri();
    break;

    case 2:
    personelIslemleri();
    break;

    case 0:
    break;

    default:
    printf("Yanlis secim yaptiniz");
    break;

  }
   
   secim=menu();

  }

 printf("Programdan cikiliyor...");
 

 return 0;

}



