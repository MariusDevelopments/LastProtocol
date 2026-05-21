# Src Klasörü

Bu klasör, teslim formatında istenen kaynak kod düzenini içerir. Unreal Engine projelerinde motorun varsayılan derleme klasörü `Source/` olduğu için orijinal proje yapısı korunmuştur; burada aynı C++ kaynak dosyaları kategori bazlı olarak düzenlenmiş teslim kopyası şeklinde yer alır.

## Kategoriler

| Klasör | İçerik |
| --- | --- |
| `core/` | Ana karakter, oyun modu, player controller, silah ve modül temel dosyaları |
| `ai/` | Behavior Tree task/service dosyaları ve yapay zeka controller kodları |
| `ui/` | HUD, can barı ve arayüz widget kodları |
| `gameplay/` | Combat, platforming ve side scrolling oynanış sınıfları |
| `animation/` | Anim notify ve animasyon tetikleyici sınıfları |
| `interfaces/` | Damageable, activatable ve interactable arayüzleri |
| `build/` | Unreal Build Tool ve target yapılandırma dosyaları |

## Not

Unreal Editor içinde projeyi çalıştırırken gerçek derleme modülü olarak `LastProtocol/` kullanılmalıdır. Tam Unreal proje kökünde bu yol `Source/LastProtocol` şeklindedir. Bu `Src/` klasörü GitHub tesliminde öğretmenin istediği kaynak kod sınıflandırmasını göstermek için hazırlanmıştır.
