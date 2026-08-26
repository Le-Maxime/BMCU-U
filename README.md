# 🚀 Ultimate BMCU Firmware

<div align="center">

[![Fork](https://img.shields.io/badge/Forked%20from-jarczakpawel%2FBMCU--C--PJARCZAK-blue.svg)](https://github.com/jarczakpawel/BMCU-C-PJARCZAK)
[![GitHub release](https://img.shields.io/github/v/release/Le-Maxime/BMCU-U?color=green)](https://github.com/Le-Maxime/BMCU-U/releases)
[![License](https://img.shields.io/badge/License-GPL%20v3-orange.svg)](LICENSE)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-Build%20Passing-brightgreen.svg)](https://github.com/Le-Maxime/BMCU-U/actions)

**Единая ультимативная сборка прошивки для мультиколор-контроллеров BMCU (Tree Tribe v2.2 / DM / Standard) с поддержкой принтеров Bambu Lab A1, A1 Mini, P1S, X1C, P2S.**

[**🌐 Онлайн-конфигуратор и скачивание прошивок**](https://raw.githack.com/Le-Maxime/BMCU-U/main/bmcu_configurator.html)

</div>

---

## 🌟 Что это такое?

Этот репозиторий представляет собой форк оригинального проекта [**jarczakpawel/BMCU-C-PJARCZAK**](https://github.com/jarczakpawel/BMCU-C-PJARCZAK), объединивший в себе **лучшие наработки и исправления из всех ключевых форков сообщества**:

| Форк / Источник | Что интегрировано в Ultimate BMCU |
|---|---|
| **[JustablockCode / BMCU-X](https://github.com/JustablockCode/BMCU-X)** | ✅ Полная совместимость с новейшими прошивками **Bambu Lab A1 / A1 Mini `v01.08.01.00+`** (версия `01.00.06.87`). |
| **[ye-cao / BMCU-C-PJARCZAK](https://github.com/ye-cao/BMCU-C-PJARCZAK)** | ✅ **DM (Dual Microswitch)** логика: аппаратная автозагрузка прутка по первому концевику, умный откат и досыл прутка.<br>✅ Оптимизация памяти Flash (убраны `double` и 64-битный модуль, сохранено **4.6+ КБ Flash**). |
| **[DZRAB / BMCU-C-PJARCZAK](https://github.com/DZRAB/BMCU-C-PJARCZAK)** | ✅ **Бесшумный ШИМ 36 кГц** (`TIM_Prescaler = 0`) — моторы работают без высокочастотного писка.<br>✅ **PR #101**: Приглушение яркости светодиодов каналов при печати. |
| **Сообщество / PR #134** | ✅ Дросселирование обновления светодиодов (10 мс) для разгрузки главного цикла микроконтроллера. |
| **Ultimate BMCU Fixes** | ✅ Устранены циклические отвалы связи и спам регистрации (`have_registered latch` + таймаут 2500 мс).<br>✅ Полностью удалён неиспользуемый код (ESP32 UART дебаг, I2C термодатчики, OLED), освобождено **~8 КБ Flash**. |

---

## 🎛 Онлайн Конфигуратор прошивок

Для удобства выбора параметров создан интерактивный веб-конфигуратор:

### 👉 [**Открыть Ultimate BMCU Configurator**](https://raw.githack.com/Le-Maxime/BMCU-U/main/bmcu_configurator.html)

Конфигуратор позволяет в один клик:
1. Выбрать тип платы (**DM с автозагрузкой** или **Стандартная**).
2. Выбрать модель принтера (**A1 / A1 Mini** или **P1 / X1 / P2**).
3. Выбрать режим загрузки (**Hard Load** или **Soft Load** для мягких пластиков).
4. Выбрать режим RGB (**Стандартный** или **Цвет прутка из слайсера**).
5. Выбрать слот AMS (**A, B, C, D**) и длину отката (**от 50 до 500 мм**).
6. Сразу же скачать готовый `.bin` файл с GitHub Releases!

---

## 🖨️ Совместимость с принтерами

| Принтер | Тип шины | Статус | Примечание |
|---|:---:|:---:|---|
| **Bambu Lab A1** | AMS / BambuBus | ✅ Работает | Протестировано на FW `01.08.01.00` |
| **Bambu Lab A1 Mini** | AMS / BambuBus | ✅ Работает | Протестировано на FW `01.08.01.00` |
| **Bambu Lab P1P / P1S** | AMS (RS485) | ✅ Работает | Используйте флаг `BMCU_P1S=1` |
| **Bambu Lab X1 / X1C** | AMS (RS485) | ✅ Работает | Используйте флаг `BMCU_P1S=1` |
| **Bambu Lab P2S / H2D** | AMS | ✅ Работает | Используйте флаг `BMCU_P1S=1` |

---

## 📦 Формат названий готовых файлов прошивок

Все файлы автоматически компилируются через **GitHub Actions** и доступны в [**Releases**](https://github.com/Le-Maxime/BMCU-U/releases):

```
bmcu_{принтер}_{плата}_ams{слот}_{ретракт}mm[_soft][_rgb].bin
```

* **`a1` / `p1s`** — модель принтера (A1 / A1 Mini или P1 / X1 / P2).
* **`dm` / `std`** — плата с двумя концевиками (DM) или с одним (Standard).
* **`amsa` .. `amsd`** — номер устройства на шине (A=0, B=1, C=2, D=3).
* **`0095mm`** — длина ретракта (например, 95 мм = 9.5 см).
* **`_soft`** *(опционально)* — режим плавной загрузки для TPU/гибких материалов.
* **`_rgb`** *(опционально)* — подсветка светодиодами точного цвета филамента из слайсера.

**Пример:** `bmcu_a1_dm_amsa_0095mm.bin` — для Bambu Lab A1, платы DM, слота A и отката 95 мм.

---

## ⚡ Инструкция по первой прошивке (CH32V203)

1. Скачайте утилиту **WCHISPTool** (или используйте `wchisp` / `OpenOCD`).
2. Зажмите кнопку **BOOT0** на плате BMCU и подключите плату к компьютеру по USB (Type-C).
3. В программе выберите чип **CH32V203C8T6** (серия CH32V20x).
4. Выберите скачанный `.bin` файл и нажмите **Download**.
5. После успешной прошивки отключите и снова подключите USB или кабель шины к принтеру.

> [!IMPORTANT]
> **Первый запуск:** При первом включении после прошивки **все 4 канала должны быть пусты** (без прутка). Плата выполнит автоматическую калибровку датчиков пустого канала.

---

## 🛠 Ручная сборка через PlatformIO

Если вам требуется собрать прошивку локально со специфическими параметрами:

```bash
# Клонирование репозитория
git clone https://github.com/Le-Maxime/BMCU-U.git
cd Ultimate-BMCU

# Пример сборки варианта под A1, плату DM, слот A, ретракт 95 мм:
pio run -e moj

# Или сборка базового окружения с произвольными флагами:
pio run -e base \
  --build-flag=-DBAMBU_BUS_AMS_NUM=0 \
  --build-flag=-DAMS_RETRACT_LEN=0.095f \
  --build-flag=-DBMCU_DM_TWO_MICROSWITCH=1
```

Бинарник появится по пути `.pio/build/<env>/firmware.bin`.

---

## 🤝 Благодарности и Авторы (Credits)

Огромная благодарность разработчикам и энтузиастам, чей код лёг в основу этой сборки:

* **[Paweł Jarczak (@jarczakpawel)](https://github.com/jarczakpawel)** — создатель и автор оригинального репозитория [BMCU-C-PJARCZAK](https://github.com/jarczakpawel/BMCU-C-PJARCZAK).
* **[ye-cao](https://github.com/ye-cao)** — разработка логики платы DM (двойные концевики) и оптимизация памяти Flash.
* **[DZRAB](https://github.com/DZRAB)** — патч тихой ШИМ 36 кГц и регулировка яркости светодиодов.
* **[JustablockCode](https://github.com/JustablockCode)** — исследование совместимости с прошивками Bambu Lab `v01.08.x` (BMCU-X).
* Всем участникам сообщества Bambu Lab Open-Source Multi-Color.

---

## 📄 Лицензия

Проект распространяется под лицензией **GPL-3.0 License**, как и оригинальный проект BMCU. Подробности в файле [LICENSE](LICENSE).