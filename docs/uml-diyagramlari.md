# UML Diyagramları

Bu dosyadaki diyagramlar Mermaid formatındadır. GitHub, Markdown içinde Mermaid bloklarını otomatik olarak görselleştirir.

## Kullanım Senaryosu Diyagramı

```mermaid
flowchart LR
    Oyuncu(["Oyuncu"])
    Sistem["Last Protocol Oyun Sistemi"]

    Oyuncu --> Hareket["Karakteri hareket ettirir"]
    Oyuncu --> Bakis["Kamerayı kontrol eder"]
    Oyuncu --> Ates["Silahla ateş eder"]
    Oyuncu --> CanTakip["HUD üzerinden canı takip eder"]

    Sistem --> Hasar["Hasar hesaplar"]
    Sistem --> HudGuncelle["Can barı ve yüzde yazısını günceller"]
    Sistem --> Olum["Can sıfırsa ölüm durumunu çalıştırır"]
    Sistem --> YapayZeka["Düşman yapay zekasını yönetir"]
```

## Sınıf Diyagramı

```mermaid
classDiagram
    class ALastProtocolCharacter {
        +float MaxHealth
        +float Health
        +bool IsAlive
        +AGun* Gun
        +Shoot()
        +UpdateHUD()
        +OnDamageTaken()
    }

    class AGun {
        +float BulletDamage
        +float MaxRange
        +AController* OwnerController
        +PullTrigger()
    }

    class UHUDWidget {
        +UProgressBar* HealthBar
        +UTextBlock* HealthPercentText
        +SetHealthBarPercent(float NewPercent)
    }

    class ALastProtocolPlayerController {
        +TSubclassOf~UHUDWidget~ HUDWidgetClass
        +UHUDWidget* HUDWidget
        +BeginPlay()
        +SetupInputComponent()
    }

    class AShooterAI {
        +ALastProtocolCharacter* MyCharacter
        +ALastProtocolCharacter* PlayerCharacter
        +StartBehaviorTree()
    }

    ALastProtocolCharacter --> AGun : silah kullanır
    ALastProtocolCharacter --> UHUDWidget : can bilgisini günceller
    ALastProtocolPlayerController --> UHUDWidget : oluşturur
    AShooterAI --> ALastProtocolCharacter : kontrol eder
    AGun --> ALastProtocolCharacter : hasar uygular
```

## Ateş Etme ve Hasar Alma Sıra Diyagramı

```mermaid
sequenceDiagram
    actor Oyuncu
    participant Karakter as ALastProtocolCharacter
    participant Silah as AGun
    participant HasarSistemi as Unreal Damage System
    participant HUD as UHUDWidget

    Oyuncu->>Karakter: Shoot()
    Karakter->>Silah: PullTrigger()
    Silah->>Silah: LineTraceSingleByChannel()
    Silah->>HasarSistemi: ApplyDamage(HitActor)
    HasarSistemi->>Karakter: OnDamageTaken()
    Karakter->>Karakter: Health = Health - Damage
    Karakter->>HUD: SetHealthBarPercent(Health / MaxHealth)
    HUD->>HUD: HealthBar ve HealthPercentText güncellenir
```

## HUD Güncelleme Aktivite Diyagramı

```mermaid
flowchart TD
    Basla([Hasar alındı])
    CanAzalt["Can değeri azaltılır"]
    Clamp["Can 0 ile MaxHealth arasında sınırlandırılır"]
    Yuzde["Can yüzdesi hesaplanır"]
    Bar["HealthBar güncellenir"]
    Yazi["HealthPercentText güncellenir"]
    Kontrol{"Can <= 0 mı?"}
    Olum["Karakter öldü durumuna geçer"]
    Bitis([Bitiş])

    Basla --> CanAzalt --> Clamp --> Yuzde --> Bar --> Yazi --> Kontrol
    Kontrol -- Evet --> Olum --> Bitis
    Kontrol -- Hayır --> Bitis
```
