# Minishell - Bir Kabuk Kadar Güzel

## Giriş
Minishell, sıfırdan basit bir Unix kabuğu (bash'e benzer) oluşturmanı sağlayan bir projedir. Bu proje, süreç oluşturma, dosya tanıtıcıları, sinyal işleme ve komut ayrıştırma gibi önemli kavramları anlamanı ve uygulamanı hedefler.

## Kurulum
Projeyi klonlayarak başlayın:

 ```bash
git clone https://github.com/akcankaan/minishell.git
cd Minishell
```

Makefile kullanarak projeyi derleyin:
 ```bash
make
```

Minishell'i başlatın:
 ```bash
./minishell
```

## Özellikler
Minishell şu özellikleri destekler:
#### Komut istemi: 
Kullanıcı girişini bekleyen bir komut istemi görüntüler.
#### Komut yürütme: 
Komutları PATH değişkenine ya da göreceli/absolüt yollara göre çalıştırır.
#### Yerleşik komutlar:
- echo (opsiyonel -n ile)
- cd (göreceli veya absolüt yol ile)
- pwd
- export
- unset
- env
- exit
#### Sinyal Yönetimi:
- ctrl-C: Yeni bir satırda yeni bir komut istemi gösterir.
- ctrl-D: Shell'den çıkış yapar.
- ctrl-\: Hiçbir işlem yapmaz (bash'te olduğu gibi).
#### Yönlendirmeler:
- <: Girdi yönlendirmesi.
- >: Çıktı yönlendirmesi.
- <<: Belirtilen sonlandırıcıya kadar girdiyi okuyan heredoc.
- >>: Ekleme modunda çıktı yönlendirmesi.
#### Boru hattı (pipe):
| karakteri ile komutları zincirleyerek birbirine bağlar.
#### Çevresel değişkenler: 
$DEĞİŞKEN ve $? son komutun çıkış durumu gibi çevresel değişkenlerin genişletilmesini sağlar.
#### Tek ve çift tırnaklar: 
' ve " karakterlerinin doğru şekilde işlenmesi.
## Gereksinimler
- 42 Normuna uygun C dilinde yazılmıştır.
- readline() fonksiyonu haricinde bellek sızıntısı bulunmamalıdır.
- Makefile, -Wall -Wextra -Werror bayraklarıyla programı derlemelidir.
- readline gibi harici kütüphanelerin kullanımı serbesttir.

## Geliştiriciler

- [Mehmet Kaan Akcan](https://github.com/akcankaan)
- [İbrahim Ecer](https://github.com/ibrahimecer)
Bu proje bizim 42Kocaeli de yaptığımız bir projedir. Bu repodaki bilgiler proje ile ilgili kısa bilgilendirmeleri içerir.


