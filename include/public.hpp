#ifndef PUBLIC_H
#define PUBLIC_H

enum EnmsgType{
    LOGIN_MSG = 1,
    LOGIN_MSG_ACK,
    LOGINOUT_MSG, // 注销消息
    REG_MSG,
    REG_MSG_ACK, // 注册响应

    ONE_CHAT_MSG,// 聊天消息
    ADD_FRIEND_MSG, // 添加好友
    CREATE_GROUP_MSG,  // 创建群组
    ADD_GROUP_MSG,  // 加入群组
    GROUP_CHAT_MSG, //群聊天

    
};
#endif