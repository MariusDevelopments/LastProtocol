# Last Protocol

## Proje Amacı

Last Protocol, Unreal Engine ile geliştirilmiş üçüncü şahıs aksiyon/nişancı oyun demosudur. Projede oyuncu karakteri hareket edebilir, silah kullanabilir, düşmanlardan veya hasar kaynaklarından can kaybedebilir ve kalan canını HUD üzerindeki can barı ile yüzde yazısından takip edebilir.

## Kullanılan Teknolojiler

- Unreal Engine
- C++
- Blueprint / Widget Blueprint
- Enhanced Input
- Behavior Tree / Blackboard
- UMG
- Niagara

## Proje Özellikleri

- Third person karakter kontrolü
- Kamera ve hareket sistemi
- Silah ile ateş etme
- Raycast tabanlı isabet kontrolü
- Hasar alma ve can azaltma sistemi
- HUD üzerinde can barı
- HUD üzerinde can yüzdesi yazısı
- Yapay zeka davranışları
- Ateş ve isabet efektleri

## Klasör Yapısı

```text
docs/
  gereksinim-analizi.md
  uml-diyagramlari.md
  ek-dokumantasyon.md

Src/
  ai/
  animation/
  build/
  core/
  gameplay/
  interfaces/
  ui/

LastProtocol/
  Unreal C++ kaynak modülü

LastProtocol.Target.cs
LastProtocolEditor.Target.cs
README.md
```

## Dokümantasyon

- Gereksinim analizi: `docs/gereksinim-analizi.md`
- UML diyagramları: `docs/uml-diyagramlari.md`
- Ek dokümantasyon: `docs/ek-dokumantasyon.md`
- Kaynak kod sınıflandırması: `Src/README.md`

## Kurulum ve Çalıştırma

1. Bilgisayarda Unreal Engine kurulu olmalıdır.
2. C++ derleme için Visual Studio 2022 ve "Desktop development with C++" bileşeni kurulu olmalıdır.
3. Proje GitHub üzerinden indirilir veya klonlanır.
4. Proje klasöründeki `.uproject` dosyası Unreal Engine ile açılır.
5. Unreal Editor açıldığında gerekirse `Compile` butonuna basılır.
6. Ana demo haritası açılır.
7. `Play` butonuna basılarak demo çalıştırılır.

## Demo Kontrol Adımları

1. Oyuncu karakterinin hareket ettiği kontrol edilir.
2. Kamera kontrolünün çalıştığı kontrol edilir.
3. Ateş etme sistemi test edilir.
4. Karakter hasar aldığında can barının azaldığı kontrol edilir.
5. Can barının yanındaki yüzde yazısının hasara göre güncellendiği kontrol edilir.
6. Can sıfıra düştüğünde karakterin öldü durumuna geçtiği doğrulanır.

## HUD Ayarları

Widget Blueprint içinde can göstergesinin çalışması için şu isimler kullanılmalıdır:

- Progress Bar: `HealthBar`
- Text Block: `HealthPercentText`

C++ tarafında `UHUDWidget::SetHealthBarPercent` fonksiyonu bu iki bileşeni aynı anda günceller.

## Unreal Kaynak Yapısı Notu

Bu klasör şu an Unreal projesinin `Source` klasörü olarak çalışmaktadır. Bu yüzden yerel dosya ağacında C++ modülü `LastProtocol/` olarak görünür. Tam Unreal proje kökünde aynı dosyaların yolu normalde `Source/LastProtocol` olur.

## GitHub Teslim Notu

GitHub'a yüklerken çalışan demo için Unreal projesinin `.uproject`, `Content`, `Config` ve `Source` dosyaları da repoda bulunmalıdır. Bu teslim düzeninde ayrıca öğretmenin istediği `docs/`, `Src/` ve `README.md` dosyaları hazırlanmıştır.
