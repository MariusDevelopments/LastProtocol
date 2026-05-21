# Gereksinim Analizi

## Proje Adı

Last Protocol

## Proje Amacı

Last Protocol, Unreal Engine ile geliştirilen üçüncü şahıs kamera açısına sahip bir aksiyon/nişancı oyun demosudur. Oyuncu karakteri harita içinde hareket eder, silah kullanarak hedeflere ateş eder, düşmanlardan hasar alır ve ekrandaki HUD üzerinden can durumunu takip eder.

## Hedef Kullanıcılar

- Aksiyon/nişancı türünde kısa bir oyun demosu deneyimlemek isteyen kullanıcılar.
- Unreal Engine ile karakter kontrolü, yapay zeka, silah sistemi ve HUD geliştirme örneği görmek isteyen öğrenciler.
- Projenin kaynak kodunu inceleyerek oyun programlama mantığını anlamak isteyen geliştiriciler.

## Fonksiyonel Gereksinimler

| No | Gereksinim | Açıklama |
| --- | --- | --- |
| F1 | Karakter kontrolü | Oyuncu karakteri klavye/fare veya desteklenen input sistemiyle hareket edebilmelidir. |
| F2 | Kamera kontrolü | Oyuncu çevreye bakabilmeli ve karakteri yönlendirebilmelidir. |
| F3 | Silah sistemi | Oyuncu ve uygun yapay zeka karakterleri silah kullanarak ateş edebilmelidir. |
| F4 | Raycast isabet sistemi | Ateş edildiğinde çizgisel izleme ile hedef vurulup vurulmadığı belirlenmelidir. |
| F5 | Hasar sistemi | Vurulan karakter veya nesne belirlenen hasar miktarına göre can kaybetmelidir. |
| F6 | Can barı | Oyuncunun güncel canı HUD üzerindeki progress bar ile gösterilmelidir. |
| F7 | Can yüzdesi yazısı | Can barının yanında güncel can yüzdesi `%100`, `%90` gibi yazı olarak gösterilmelidir. |
| F8 | Ölüm durumu | Oyuncunun canı sıfıra indiğinde karakter öldü durumuna geçmeli ve kontrol dışı kalmalıdır. |
| F9 | Yapay zeka | Düşman karakterleri oyuncuyu algılayıp davranış ağacı üzerinden aksiyon alabilmelidir. |
| F10 | Görsel ve ses efektleri | Ateş etme ve isabet durumlarında efekt ve ses kullanılmalıdır. |

## Fonksiyonel Olmayan Gereksinimler

| No | Gereksinim | Açıklama |
| --- | --- | --- |
| NF1 | Kullanılabilirlik | HUD sade, okunabilir ve oyun sırasında hızlı takip edilebilir olmalıdır. |
| NF2 | Performans | Oyun demosu akıcı çalışmalı, gereksiz işlem yükünden kaçınılmalıdır. |
| NF3 | Modülerlik | Kaynak kodlar karakter, silah, yapay zeka, arayüz ve oynanış mantığı olarak ayrılmalıdır. |
| NF4 | Genişletilebilirlik | Yeni düşman, silah veya arayüz bileşeni eklemek kolay olmalıdır. |
| NF5 | Bakım kolaylığı | Kod dosyaları anlaşılır isimlendirilmeli ve görevlerine göre klasörlenmelidir. |

## Kullanım Senaryoları

| Senaryo | Aktör | Açıklama |
| --- | --- | --- |
| Oyuna başlama | Oyuncu | Oyuncu demoyu başlatır ve karakteri kontrol eder. |
| Hareket etme | Oyuncu | Oyuncu karakteri ileri, geri, sağ ve sola hareket ettirir. |
| Ateş etme | Oyuncu | Oyuncu silahı tetikler ve hedefe hasar verir. |
| Hasar alma | Oyuncu / Düşman | Karakter vurulduğunda can değeri düşer. |
| Can takibi | Oyuncu | Oyuncu HUD üzerindeki bar ve yüzde yazısından kalan canı görür. |
| Ölme | Oyuncu | Can sıfıra indiğinde karakterin canlılık durumu kapanır. |

## Kısıtlar ve Varsayımlar

- Proje Unreal Engine üzerinde C++ ve Blueprint iş akışıyla geliştirilmiştir.
- Projenin çalışması için Unreal Engine ve gerekli C++ geliştirme araçları kurulu olmalıdır.
- HUD widget tasarımı Unreal Editor içinden yapılır; C++ tarafı widget bileşenlerini isimleriyle bağlar.
- Demo kapsamı akademik teslim için hazırlanmıştır; tam ürün seviyesinde menü, kayıt sistemi veya yayınlama paketi zorunlu değildir.
