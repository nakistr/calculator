Markdown

# Postfix Expression Solver (Brute-Force)

Bu proje, input.txt dosyasından okunan bir *Postfix (Reverse Polish Notation)* ifadesini analiz eden ve ifade içindeki a, b ve c değişkenlerinin yerine gelebilecek uygun değerleri bulan bir C uygulamasıdır.

Program, verilen ifadenin sonucunu *0*'a eşitleyen tüm olası (a, b, c) kombinasyonlarını (sayı veya operatör) *brute-force (kaba kuvvet)* yöntemiyle hesaplar.

## 🚀 Özellikler

* *Özel Yığın (Stack) Yapısı:* struct kullanılarak manuel olarak oluşturulmuş dinamik Stack yapısı.
* *Postfix Değerlendirme:* Standart matematiksel işlem önceliği derdi olmadan ifadeleri soldan sağa işleme.
* *Çok Yönlü Değişken Çözümü:* a, b ve c değişkenleri hem *sayı* (1-30 arası) hem de *operatör* (+, -, *, /, ^) olabilir.
* *Sözdizimi Doğrulama (Validity Check):* Rastgele denenen kombinasyonların geçerli bir matematiksel ifade oluşturup oluşturmadığını kontrol eden algoritma.
* *Desteklenen Operatörler:* Toplama (+), Çıkarma (-), Çarpma (*), Bölme (/), Üs Alma (^).

## 🛠 Nasıl Çalışır?

1.  Program input.txt dosyasını okur. (Örn: 10 a 5 b =)
2.  İfadeyi parçalarına (token) ayırır.
3.  a, b ve c için olası türleri (Sayı veya Operatör) belirler.
4.  İç içe döngülerle 1'den 30'a kadar olan sayıları ve mevcut operatörleri dener.
5.  Her kombinasyon için önce *geçerlilik kontrolü* yapar (ifade mantıklı mı?), ardından *postfix hesaplaması* yapar.
6.  Sonucun 0 olduğu tüm kombinasyonları ekrana basar.

## 📋 Gereksinimler ve Derleme

Bu projeyi çalıştırmak için bilgisayarınızda bir C derleyicisine (GCC gibi) ihtiyacınız vardır.

### Derleme (Compile)
Terminal veya komut satırında proje dizinine giderek şu komutu çalıştırın:

bash
gcc main.c -o postfix_solver
Çalıştırma (Run)
Derleme işleminden sonra programı çalıştırın:

Windows:

Bash

postfix_solver.exe
Linux / Mac:

Bash

./postfix_solver
📄 Girdi Formatı (input.txt)
Programın çalışması için proje dizininde input.txt adında bir dosya olmalıdır. Dosya formatı şu kurallara uymalıdır:

Kelimeler/Sayılar arasında birer boşluk olmalıdır.

İfade Postfix formatında yazılmalıdır.

İfadenin sonu = işareti ile bitmelidir (ancak kod = işaretini işlemeyi durdurma noktası olarak kullanır).

Örnek input.txt içeriği:

Plaintext

10 a 5 - * 20 - =
(Bu örnekte program, ifadenin sonucunu 0 yapacak 'a' değerini arayacaktır.)

⚠ Sınırlamalar
Program şu an için sayısal değer aralıklarını 1 ile 30 arasında sınırlar (Performans optimizasyonu için MAX_NUM = 30).

Bölme işlemlerinde tam sayı bölmesi (integer division) kullanılır ve sıfıra bölme hataları kontrol edilir.

🤝 Katkıda Bulunma
Hataları düzeltmek veya algoritmayı geliştirmek isterseniz Pull Request göndermekten çekinmeyin.


---

### İsteğe Bağlı: `.gitignore`
Projeyi GitHub'a yüklerken gereksiz dosyaların yüklenmemesi için bir `.gitignore` dosyası oluşturmanızı da öneririm:

text
# .gitignore
*.exe
*.o
input.txt
.DS_Store
