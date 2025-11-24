#include "abs_key_cfg.h"
#include "abs_key_callback.h"

const Abs_Key_DebounceTimer_t Abs_Key_DebounceTimerCallBack_Table[KEYMAX_NUM] =
    {
        {
            .key_index = KEY0,
            .callback = Abs_Key_Key0_Debounce_Callback,
        },
        {
            .key_index = KEY1,
            .callback = Abs_Key_Key1_Debounce_Callback,
        },
        {
            .key_index = KEY2,
            .callback = Abs_Key_Key2_Debounce_Callback,
        },
        {
            .key_index = KEY3,
            .callback = Abs_Key_Key3_Debounce_Callback,
        },

};

const Abs_Key_CallBack_t Abs_Key_Key0_Event_Table[ABS_KEY_EVENT_NUM] =
    {
        {
            .event = ABS_KEY_EVENT_SINGLE_CLICK,
            .callback = Abs_Key_Key0_Event_Single_Click,
        },
        {
            .event = ABS_KEY_EVENT_DOUBLE_CLICK,
            .callback = Abs_Key_Key0_Event_Double_Click,
        },
        {
            .event = ABS_KEY_EVENT_TRIPLE_CLICK,
            .callback = Abs_Key_Key0_Event_Triple_Click,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS,
            .callback = Abs_Key_Key0_Event_Long_Press,
        },
        {
            .event = ABS_KEY_EVENT_LONG_REPEAT,
            .callback = Abs_Key_Key0_Event_Long_Press_Repeat,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS_RELEASE,
            .callback = Abs_Key_Key0_Event_Long_Press_Release,
        },
};

const Abs_Key_CallBack_t Abs_Key_Key1_Event_Table[ABS_KEY_EVENT_NUM] =
    {
        {
            .event = ABS_KEY_EVENT_SINGLE_CLICK,
            .callback = Abs_Key_Key1_Event_Single_Click,
        },
        {
            .event = ABS_KEY_EVENT_DOUBLE_CLICK,
            .callback = Abs_Key_Key1_Event_Double_Click,
        },
        {
            .event = ABS_KEY_EVENT_TRIPLE_CLICK,
            .callback = Abs_Key_Key1_Event_Triple_Click,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS,
            .callback = Abs_Key_Key1_Event_Long_Press,
        },
        {
            .event = ABS_KEY_EVENT_LONG_REPEAT,
            .callback = Abs_Key_Key1_Event_Long_Press_Repeat,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS_RELEASE,
            .callback = Abs_Key_Key1_Event_Long_Press_Release,
        },
};

const Abs_Key_CallBack_t Abs_Key_Key2_Event_Table[ABS_KEY_EVENT_NUM] =
    {
        {
            .event = ABS_KEY_EVENT_SINGLE_CLICK,
            .callback = Abs_Key_Key2_Event_Single_Click,
        },
        {
            .event = ABS_KEY_EVENT_DOUBLE_CLICK,
            .callback = Abs_Key_Key2_Event_Double_Click,
        },
        {
            .event = ABS_KEY_EVENT_TRIPLE_CLICK,
            .callback = Abs_Key_Key2_Event_Triple_Click,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS,
            .callback = Abs_Key_Key2_Event_Long_Press,
        },
        {
            .event = ABS_KEY_EVENT_LONG_REPEAT,
            .callback = Abs_Key_Key2_Event_Long_Press_Repeat,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS_RELEASE,
            .callback = Abs_Key_Key2_Event_Long_Press_Release,
        },
};

const Abs_Key_CallBack_t Abs_Key_Key3_Event_Table[ABS_KEY_EVENT_NUM] =
    {
        {
            .event = ABS_KEY_EVENT_SINGLE_CLICK,
            .callback = Abs_Key_Key3_Event_Single_Click,
        },
        {
            .event = ABS_KEY_EVENT_DOUBLE_CLICK,
            .callback = Abs_Key_Key3_Event_Double_Click,
        },
        {
            .event = ABS_KEY_EVENT_TRIPLE_CLICK,
            .callback = Abs_Key_Key3_Event_Triple_Click,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS,
            .callback = Abs_Key_Key3_Event_Long_Press,
        },
        {
            .event = ABS_KEY_EVENT_LONG_REPEAT,
            .callback = Abs_Key_Key3_Event_Long_Press_Repeat,
        },
        {
            .event = ABS_KEY_EVENT_LONG_PRESS_RELEASE,
            .callback = Abs_Key_Key3_Event_Long_Press_Release,
        },
};

const Abs_Key_CallBackCfg_t Abs_Key_CallBackCfg_Table[KEYMAX_NUM] =
    {
        {
            .key_index = KEY0,
            .key_event_table = Abs_Key_Key0_Event_Table,
        },
        {
            .key_index = KEY1,
            .key_event_table = Abs_Key_Key1_Event_Table,
        },
        {
            .key_index = KEY2,
            .key_event_table = Abs_Key_Key2_Event_Table,
        },
        {
            .key_index = KEY3,
            .key_event_table = Abs_Key_Key3_Event_Table,
        },
};
