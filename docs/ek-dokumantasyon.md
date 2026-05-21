# Ek Dokümantasyon

## Teknoloji Seçimi

Projede Unreal Engine tercih edilmiştir. Unreal Engine, C++ desteği, Blueprint entegrasyonu, hazır karakter sistemi, animasyon araçları, yapay zeka bileşenleri ve HUD geliştirme olanakları sayesinde oyun demosu geliştirmek için uygundur.

## Kullanılan Başlıca Teknolojiler

| Teknoloji | Kullanım Amacı |
| --- | --- |
| Unreal Engine | Oyun motoru, sahne yönetimi, karakter sistemi ve oynanış altyapısı |
| C++ | Karakter, silah, hasar, HUD ve yapay zeka mantığı |
| Blueprint / Widget Blueprint | Görsel arayüz, asset bağlama ve editör içi ayarlar |
| Enhanced Input | Klavye, fare ve input mapping yönetimi |
| Behavior Tree / Blackboard | Düşman yapay zekası davranış yönetimi |
| Niagara | Ateş ve isabet efektleri |
| UMG | Can barı ve can yüzdesi arayüzü |

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

README.md
```

Unreal Engine projelerinde gerçek derleme klasörü varsayılan olarak `Source/` adını kullanır. Bu çalışma alanı doğrudan `Source` klasörü olduğu için C++ modülü `LastProtocol/` altında görünür. Tam proje kökünde aynı yapı `Source/LastProtocol` yoluna karşılık gelir. Bu teslimde öğretmenin istediği format için kaynak kodlar `Src/` altında kategori bazlı olarak ayrıca düzenlenmiştir.

## HUD Can Yüzdesi Notu

Can barının yanında yüzde yazısının çalışması için Widget Blueprint içinde şu isimler kullanılmalıdır:

- Progress Bar adı: `HealthBar`
- Text Block adı: `HealthPercentText`

C++ tarafında `UHUDWidget::SetHealthBarPercent` fonksiyonu hem progress bar doluluk oranını hem de yüzde yazısını günceller. Oyuncu hasar aldığında `ALastProtocolCharacter::OnDamageTaken` fonksiyonu canı azaltır ve `UpdateHUD` ile arayüzü yeniler.

## Demo Test Adımları

1. Unreal Editor ile proje açılır.
2. Ana harita veya demo level yüklenir.
3. `Play` butonuna basılır.
4. Oyuncu karakterinin hareket ettiği kontrol edilir.
5. Ateş etme tuşu ile silah sistemi test edilir.
6. Hasar alındığında can barı ve yüzde yazısının birlikte azaldığı kontrol edilir.
7. Can sıfıra indiğinde karakterin öldü durumuna geçtiği doğrulanır.

## Geliştirme Notları

- `AGun` sınıfı ateş etme, raycast ve hasar gönderme akışını yönetir.
- `ALastProtocolCharacter` sınıfı oyuncu karakterinin hareket, silah ve can mantığını taşır.
- `UHUDWidget` sınıfı HUD üzerindeki can barı ve yüzde yazısını günceller.
- `ALastProtocolPlayerController` oyun başında HUD widget'ını oluşturur.
- Yapay zeka davranışları Behavior Tree ve ilgili BT task/service sınıfları ile yönetilir.
