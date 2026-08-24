#ifndef BMCU_LINK_H
#define BMCU_LINK_H

#include <stdint.h>
#include <stdbool.h>

/* 编译宏：启用 bmcu_link 诊断伴侣协议（需要 USART3 硬件）。默认关闭。 */
#ifndef BMCU_LINK_ENABLED
#define BMCU_LINK_ENABLED 0
#endif

/* 编译宏：启用完整状态快照（GET_FULL_STATUS）。禁用可节省 ~3KB Flash。 */
#ifndef BMCU_LINK_FULL_STATUS
#define BMCU_LINK_FULL_STATUS 1
#endif

enum bmcu_status_change : uint32_t
{
    BMCU_STATUS_CHANGE_SLOT     = 1u << 0,
    BMCU_STATUS_CHANGE_INSERTED = 1u << 1,
    BMCU_STATUS_CHANGE_ONLINE   = 1u << 2,
    BMCU_STATUS_CHANGE_MOTION   = 1u << 3,
    BMCU_STATUS_CHANGE_PRESSURE = 1u << 4,
    BMCU_STATUS_CHANGE_LED      = 1u << 5,
    BMCU_STATUS_CHANGE_ERROR    = 1u << 6,
    BMCU_STATUS_CHANGE_ALL      = 0x7Fu,
};

#if BMCU_LINK_ENABLED

void bmcu_link_init(void);
void bmcu_link_service(void);
void bmcu_link_rx_isr_byte(uint8_t data);
void bmcu_link_apply_led_override(void);
void bmcu_link_set_control_error(int error);
void bmcu_link_set_calibration_busy(bool busy);
void bmcu_link_status_changed(uint32_t reasons);
void bmcu_link_printer_transaction(uint8_t rx_class, uint8_t command, uint8_t outcome,
                                   uint8_t reason, uint16_t request_length,
                                   uint16_t response_length);
void bmcu_link_printer_long_transaction(uint16_t type, uint8_t outcome, uint8_t reason,
                                        uint16_t payload_length, uint16_t response_length,
                                        uint8_t payload_hash);
void bmcu_link_ams_service_poll(void);
void bmcu_link_ams_service_frame(uint8_t service_kind);
void bmcu_link_ams_registration_query(void);
void bmcu_link_ams_registration_confirm(void);
void bmcu_link_ams_registration_reset(void);
void bmcu_link_motion_fault(uint8_t channel, uint8_t previous_fault, uint8_t fault);
uint32_t bmcu_link_tx_drop_count(void);
bool bmcu_link_reset_pending(void);

#else

static inline void bmcu_link_init(void) {}
static inline void bmcu_link_service(void) {}
static inline void bmcu_link_rx_isr_byte(uint8_t) {}
static inline void bmcu_link_apply_led_override(void) {}
static inline void bmcu_link_set_control_error(int) {}
static inline void bmcu_link_set_calibration_busy(bool) {}
static inline void bmcu_link_status_changed(uint32_t) {}
static inline void bmcu_link_printer_transaction(uint8_t, uint8_t, uint8_t,
                                                 uint8_t, uint16_t, uint16_t) {}
static inline void bmcu_link_printer_long_transaction(uint16_t, uint8_t, uint8_t,
                                                      uint16_t, uint16_t, uint8_t) {}
static inline void bmcu_link_ams_service_poll(void) {}
static inline void bmcu_link_ams_service_frame(uint8_t) {}
static inline void bmcu_link_ams_registration_query(void) {}
static inline void bmcu_link_ams_registration_confirm(void) {}
static inline void bmcu_link_ams_registration_reset(void) {}
static inline void bmcu_link_motion_fault(uint8_t, uint8_t, uint8_t) {}
static inline uint32_t bmcu_link_tx_drop_count(void) { return 0u; }
static inline bool bmcu_link_reset_pending(void) { return false; }

#endif

#endif
