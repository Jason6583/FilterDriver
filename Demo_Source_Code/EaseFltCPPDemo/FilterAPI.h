///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 2014 EaseFilter Technologies Inc.
//    All Rights Reserved
//
//    This software is part of a licensed software product and may
//    only be used or copied in accordance with the terms of that license.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __SHARE_TYPE_H__
#define __SHARE_TYPE_H__

//Purchase a license key with the link: http://www.EaseFilter.com/Order.htm
//Email us to request a trial key: info@EaseFilter.com //free email is not accepted.
#define	registerKey "******************************************"

#define MAX_FILE_NAME_LENGTH				1024
#define MAX_SID_LENGTH						256
#define MAX_EXCLUDED_PROCESS_ID				200	
#define MAX_INCLUDED_PROCESS_ID				200
#define MAX_PROTECTED_PROCESS_ID			200
#define MAX_BLOCK_SAVEAS_PROCESS_ID			200
#define MAX_PATH							260
#define	MAX_ERROR_MESSAGE_SIZE				1024
#define BLOCK_SIZE							65536

#define AES_VERIFICATION_KEY			0xccb76e80

//the flags for encrypted file,indicates the action to the encrypted file open I/O.
typedef enum _AESFlags
{
	Flags_Enabled_Expire_Time			=	0x00000010, 
	Flags_Enabled_Check_ProcessName		=	0x00000020, 
	Flags_Enabled_Check_UserName		=	0x00000040, 
	Flags_Enabled_Check_AccessFlags		=	0x00000080, 
	Flags_Enabled_Check_User_Permit		=	0x00000100, 
	Flags_AES_Key_Was_Embedded			=	0x00000200, 
	Flags_Request_AccessFlags_From_User	=	0x00000400, 
	Flags_Request_IV_And_Key_From_User	=	0x00000800, 
	Flags_Enabled_Check_Computer_Id		=	0x00001000, 
	Flags_Enabled_Check_User_Password	=	0x00002000, 

}AESFlags;

//This is the first AES version which is using OpenSSL encryptor
#define AES_VERSION_1 16
//this is the second version which is using Microsoft CNG lib to support AES-NI feature, only vista or later OS can support.
#define AES_VERSION_2 32

//the structure of control meta data of the encrypted file.
#pragma pack (push,1)

typedef struct _AES_DATA 
{
	ULONG		VerificationKey;
	ULONG		AESFlags;
	ULONG		Version;
	UCHAR		IV[16];
	ULONG		EncryptionKeyLength;
	UCHAR		EncryptionKey[32];
	LONGLONG	FileSize;
	ULONG		CryptoType;
	ULONG		PaddingSize;
	//the size of this data structure
	ULONG		AESDataSize;
	//the actual physical file size in disk including the padding and the header.
	LONGLONG	ShadowFileSize;
	ULONG		AccessFlags;
	ULONG		Reserve1;
	ULONG		Reserve2;
	ULONG		TagDataLength;
	WCHAR		TagData[1];
	
} AES_DATA, *PAES_DATA;

//the custom data structure for tagData inside of PAES_DATA
typedef struct _AES_TAG_CONTROL_DATA 
{
	ULONG		VerificationKey;
	ULONG		AESFlags;
	LONGLONG    CreationTime;
	LONGLONG    ExpireTime;
	ULONG		AccessFlags;
	ULONG		LengthOfIncludeProcessNames;
	ULONG		OffsetOfIncludeProcessNames;
	ULONG		LengthOfExcludeProcessNames;
	ULONG		OffsetOfExcludeProcessNames;
	ULONG		LengthOfIncludeUserNames;
	ULONG		OffsetOfIncludeUserNames;
	ULONG		LengthOfExcludeUserNames;
	ULONG		OffsetOfExcludeUserNames;
	ULONG		LengthOfAccountName;
	ULONG		OffsetOfAccountName;
	ULONG		LengthOfComputerId;
	ULONG		OffsetOfComputerId;
	ULONG		LengthOfUserPassword;
	ULONG		OffsetOfUserPassword;

	//the data store here.
	//IncludeProcessNames;
	//ExcludeProcessNames;
	//IncludeUserNames;
	//ExcludeUserNames;
	//AccountNames;
	//ComputerId;
	//UserPassword;
	
} AES_TAG_CONTROL_DATA, *PAES_TAG_CONTROL_DATA;
#pragma pack(pop)

//---------------------------------------------------------------------------------------

typedef enum _FilterType 
{
    /// <summary>
    /// File system control filter driver
    /// </summary>
    FILE_SYSTEM_CONTROL = 0x01,
    /// <summary>
    /// File system encryption filter driver
    /// </summary>
    FILE_SYSTEM_ENCRYPTION = 0x02,
    /// <summary>
    /// File system monitor filter driver
    /// </summary>
    FILE_SYSTEM_MONITOR = 0x04,
    /// <summary>
    /// File system registry filter driver
    /// </summary>
    FILE_SYSTEM_REGISTRY = 0x08,
    /// <summary>
    /// File system process filter driver
    /// </summary>
    FILE_SYSTEM_PROCESS = 0x10,
    /// <summary>
    /// File system hierarchical storage management filter driver
    /// </summary>
    FILE_SYSTEM_HSM = 0x40,
    /// <summary>
    /// File system cloud storage filter driver
    /// </summary>
    FILE_SYSTEM_CLOUD = 0x80,

} FilterType;


#define MAX_REQUEST_TYPE 32

//the commands were sent to the user mode application by filter driver.
typedef enum _FilterCommand
{	
	/// <summary>
    /// request the read data back with block data or whole cache file name.
    /// </summary>
	MESSAGE_TYPE_RESTORE_BLOCK_OR_FILE	=						0x00000001,
	/// <summary>
    /// request to download the data to the original folder.
    /// </summary>
	MESSAGE_TYPE_RESTORE_FILE_TO_ORIGINAL_FOLDER =				0x00000002,
	/// <summary>
    /// request the directory file list.
    /// </summary>
	MESSAGE_TYPE_GET_FILE_LIST =								0x00000004,
	/// <summary>
    /// request to download whole file to the cache folder.
    /// </summary>
	MESSAGE_TYPE_RESTORE_FILE_TO_CACHE =						0x00000008,
	/// <summary>
    /// send the notification event of the file changed.
    /// </summary>
	MESSAGE_TYPE_SEND_EVENT_NOTIFICATION =						0x00000010,
	/// <summary>
    /// send the notification event of the file was deleted.
    /// </summary>
	MESSAGE_TYPE_DELETE_FILE =									0x00000020,
	/// <summary>
    /// send the notification event of the file was renamed.
    /// </summary>
	MESSAGE_TYPE_RENAME_FILE =									0x00000040,
	/// <summary>
    /// send the file name of the message was stored.
    /// </summary>
	MESSAGE_TYPE_SEND_MESSAGE_FILENAME =						0x00000080,
	/// <summary>
    /// send the notification event of the file was changed.
    /// </summary>
    FILTER_SEND_FILE_CHANGED_EVENT = 0x00010001,
    /// <summary>
    /// request the file open permission.
    /// </summary>
    FILTER_REQUEST_USER_PERMIT = 0x00010002,
    /// <summary>
    /// request the encryption key for the file open or creation.
    /// </summary>
    FILTER_REQUEST_ENCRYPTION_KEY = 0x00010003,
    /// <summary>
    /// request the encryption iv and key for the encrypted file open or to encrypt the file
    /// </summary>
    FILTER_REQUEST_ENCRYPTION_IV_AND_KEY = 0x00010004,
    /// <summary>
    /// request the encryption iv, key and access flags for the encrypted file open or to encrypt the file 
    /// </summary>
    FILTER_REQUEST_ENCRYPTION_IV_AND_KEY_AND_ACCESSFLAG = 0x00010005,
    /// <summary>
    /// request the encryption iv, key and access flags  and tag data for file encryption 
    /// </summary>
    FILTER_REQUEST_ENCRYPTION_IV_AND_KEY_AND_TAGDATA = 0x00010006,
    /// <summary>
    /// send the registry access notification class information
    /// </summary>
    FILTER_SEND_REG_CALLBACK_INFO = 0x00010007,
	/// <summary>
	/// send the new process creation information
	/// </summary>
	FILTER_SEND_PROCESS_CREATION_INFO = 0x00010008,
	/// <summary>
	/// send the process termination ifnormation
	/// </summary>
	FILTER_SEND_PROCESS_TERMINATION_INFO = 0x00010009,
	/// <summary>
	/// send the new thread creation information
	/// </summary>
	FILTER_SEND_THREAD_CREATION_INFO = 0x0001000a,
	/// <summary>
	/// send the thread termination ifnormation
	/// </summary>
	FILTER_SEND_THREAD_TERMINATION_INFO = 0x0001000b,
	/// <summary>
	/// send the process handle operations information
	/// </summary>
	FILTER_SEND_PROCESS_HANDLE_INFO = 0x0001000c,
	/// <summary>
	/// send the thread handle operations ifnormation
	/// </summary>
	FILTER_SEND_THREAD_HANDLE_INFO = 0x0001000d,

}FilterCommand;

 /// <summary>
/// process filter driver control flag.
/// </summary>
typedef enum  _ProcessControlFlag 
{
    /// <summary>
    /// deny the new process creation if the flag is on
    /// </summary>
    DENY_NEW_PROCESS_CREATION = 0x00000001,
    /// <summary>
    /// Get a notification when a new process is being created.
    /// </summary>
    PROCESS_CREATION_NOTIFICATION      = 0x00000100,
    /// <summary>
    ///get a notification when a process was termiated 
    /// </summary>
    PROCESS_TERMINATION_NOTIFICATION   = 0x00000200,
    /// <summary>
    /// get a notification for process handle operations, when a handle for a process
    /// is being created or duplicated.
    /// </summary>
    PROCESS_HANDLE_OP_NOTIFICATION     = 0x00000400,
    /// <summary>
    /// get a notifcation when a new thread is being created.
    /// </summary>
    THREAD_CREATION_NOTIFICATION       = 0x00000800,
    /// <summary>
    /// get a notification when a thread was termiated 
    /// </summary>
    THREAD_TERMINIATION_NOTIFICATION   = 0x00001000,
    /// <summary>
    /// get a notification for thread handle operations, when a handle for a process
    /// is being created or duplicated.
    /// </summary>
    THREAD_HANDLE_OP_NOTIFICATION      = 0x00002000,
                                  
}ProcessControlFlag;

/// <summary>
/// This is for registry filter driver only, the registry access control flag
/// </summary>
typedef enum  _RegControlFlag
{
    REG_ALLOW_OPEN_KEY = 0x00000001,
    REG_ALLOW_CREATE_KEY = 0x00000002,
    REG_ALLOW_QUERY_KEY = 0x00000004,
    REG_ALLOW_RENAME_KEY = 0x00000008,
    REG_ALLOW_DELETE_KEY = 0x00000010,
    REG_ALLOW_SET_VALUE_KEY_INFORMATION = 0x00000020,
	REG_ALLOW_SET_INFORMATION_KEY = 0x00000040,
    REG_ALLOW_ENUMERATE_KEY = 0x00000080,
    REG_ALLOW_QUERY_VALUE_KEY = 0x00000100,
    REG_ALLOW_ENUMERATE_VALUE_KEY = 0x00000200,
    REG_ALLOW_QUERY_MULTIPLE_VALUE_KEY = 0x00000400,
    REG_ALLOW_DELETE_VALUE_KEY = 0x00000800,
    REG_ALLOW_QUERY_KEY_SECURITY = 0x00001000,
    REG_ALLOW_SET_KEY_SECRUITY = 0x00002000,
    REG_ALLOW_RESTORE_KEY = 0x00004000,
    REG_ALLOW_REPLACE_KEY = 0x00008000,
    REG_ALLOW_SAVE_KEY = 0x00010000,
	REG_ALLOW_FLUSH_KEY = 0x00020000,
	REG_ALLOW_LOAD_KEY = 0x00040000,
	REG_ALLOW_UNLOAD_KEY = 0x00080000,
	REG_ALLOW_KEY_CLOSE = 0x00100000,
	REG_ALLOW_QUERY_KEYNAME = 0x00200000,
    REG_MAX_ACCESS_FLAG = 0xFFFFFFFF,

}RegControlFlag;

/// <summary>
/// This is for registry filter driver only, the registry callback class, you can block or modify the registry access in pre-callback
/// or monitor the registry access in post-callback
/// </summary>
typedef enum  _RegCallbackClass
{
	Reg_Pre_Delete_Key = 0x00000001,
    Reg_Pre_Set_Value_Key = 0x00000002,
    Reg_Pre_Delete_Value_Key = 0x00000004,
    Reg_Pre_SetInformation_Key = 0x00000008,
    Reg_Pre_Rename_Key = 0x00000010,
    Reg_Pre_Enumerate_Key = 0x00000020,
    Reg_Pre_Enumerate_Value_Key = 0x00000040,
    Reg_Pre_Query_Key = 0x00000080,
    Reg_Pre_Query_Value_Key = 0x00000100,
    Reg_Pre_Query_Multiple_Value_Key = 0x00000200,
    Reg_Pre_Create_Key = 0x00000400,
    Reg_Post_Create_Key = 0x00000800,
    Reg_Pre_Open_Key = 0x00001000,
    Reg_Post_Open_Key = 0x00002000,
    Reg_Pre_Key_Handle_Close = 0x00004000,
    //
    // .Net only
    //    
    Reg_Post_Delete_Key = 0x00008000,
    Reg_Post_Set_Value_Key = 0x00010000,
    Reg_Post_Delete_Value_Key = 0x00020000,
    Reg_Post_SetInformation_Key = 0x00040000,
    Reg_Post_Rename_Key = 0x00080000,
    Reg_Post_Enumerate_Key = 0x00100000,
    Reg_Post_Enumerate_Value_Key = 0x00200000,
    Reg_Post_Query_Key = 0x00400000,
    Reg_Post_Query_Value_Key = 0x00800000,
    Reg_Post_Query_Multiple_Value_Key = 0x01000000,
    Reg_Post_Key_Handle_Close = 0x02000000,
    Reg_Pre_Create_KeyEx = 0x04000000,
    Reg_Post_Create_KeyEx = 0x08000000,
    Reg_Pre_Open_KeyEx = 0x10000000,
    Reg_Post_Open_KeyEx = 0x20000000,
    //
    // new to Windows Vista
    //
    Reg_Pre_Flush_Key = 0x40000000,
    Reg_Post_Flush_Key = 0x80000000,

}RegCallbackClass;

//high field for reg callback class
#define    Reg_Pre_Load_Key  (ULONGLONG)0x100000000
#define    Reg_Post_Load_Key  (ULONGLONG)0x200000000
#define    Reg_Pre_UnLoad_Key  (ULONGLONG)0x400000000
#define    Reg_Post_UnLoad_Key  (ULONGLONG)0x800000000
#define    Reg_Pre_Query_Key_Security  (ULONGLONG)0x1000000000
#define	   Reg_Post_Query_Key_Security  (ULONGLONG)0x2000000000
#define    Reg_Pre_Set_Key_Security  (ULONGLONG)0x4000000000
#define    Reg_Post_Set_Key_Security  (ULONGLONG)0x8000000000
    //
    // per-object context cleanup
    //
#define    Reg_Callback_Object_Context_Cleanup  (ULONGLONG)0x10000000000
    //
    // new in Vista SP2 
    //
#define    Reg_Pre_Restore_Key  (ULONGLONG)0x20000000000
#define    Reg_Post_Restore_Key  (ULONGLONG)0x40000000000
#define    Reg_Pre_Save_Key  (ULONGLONG)0x80000000000
#define    Reg_Post_Save_Key  (ULONGLONG)0x100000000000
#define    Reg_Pre_Replace_Key  (ULONGLONG)0x200000000000
#define    Reg_Post_Replace_Key  (ULONGLONG)0x400000000000

//
//new in Windows 10
//
#define    Reg_Pre_Query_KeyName  (ULONGLONG)0x800000000000
#define    Reg_Post_Query_KeyName  (ULONGLONG)0x1000000000000

#define    Max_Reg_Callback_Class  (ULONGLONG)0xFFFFFFFFFFFFFFFF




//the I/O types of the monitor or control filter can intercept.
typedef enum _MessageType
{
	
	PRE_CREATE							= 0x00000001,
	POST_CREATE							= 0x00000002,
	PRE_FASTIO_READ						= 0x00000004,
	POST_FASTIO_READ					= 0x00000008,
	PRE_CACHE_READ						= 0x00000010,
	POST_CACHE_READ						= 0x00000020,
	PRE_NOCACHE_READ					= 0x00000040,
	POST_NOCACHE_READ					= 0x00000080,
	PRE_PAGING_IO_READ					= 0x00000100,
	POST_PAGING_IO_READ					= 0x00000200,
	PRE_FASTIO_WRITE					= 0x00000400,
	POST_FASTIO_WRITE					= 0x00000800,
	PRE_CACHE_WRITE						= 0x00001000,
	POST_CACHE_WRITE					= 0x00002000,
	PRE_NOCACHE_WRITE					= 0x00004000,
	POST_NOCACHE_WRITE					= 0x00008000,
	PRE_PAGING_IO_WRITE					= 0x00010000,
	POST_PAGING_IO_WRITE				= 0x00020000,
	PRE_QUERY_INFORMATION				= 0x00040000,
	POST_QUERY_INFORMATION				= 0x00080000,
	PRE_SET_INFORMATION					= 0x00100000,
	POST_SET_INFORMATION				= 0x00200000,
	PRE_DIRECTORY						= 0x00400000,
	POST_DIRECTORY						= 0x00800000,
	PRE_QUERY_SECURITY					= 0x01000000,	
	POST_QUERY_SECURITY					= 0x02000000,
	PRE_SET_SECURITY					= 0x04000000,
	POST_SET_SECURITY					= 0x08000000,
	PRE_CLEANUP							= 0x10000000,
	POST_CLEANUP						= 0x20000000,
	PRE_CLOSE							= 0x40000000,
	POST_CLOSE							= 0x80000000UL, 

}MessageType;

//the flags of the access control to the file.
typedef enum _AccessFlag
{
    /// <summary>
    /// Filter driver will skip all the IO if the file name match the include file mask.
    /// </summary>
    EXCLUDE_FILTER_RULE = 0X00000000,
    /// <summary>
    /// Block the file open. 
    /// </summary>
    EXCLUDE_FILE_ACCESS = 0x00000001,
    /// <summary>
    /// Reparse the file open to the new file name if the reparse file mask was added.
    /// </summary>
    ENABLE_REPARSE_FILE_OPEN = 0x00000002,
    /// <summary>
    /// Hide the files from the folder directory list if the hide file mask was added.
    /// </summary>
    ENABLE_HIDE_FILES_IN_DIRECTORY_BROWSING = 0x00000004,
    /// <summary>
    /// Enable the transparent file encryption if the encryption key was added.
    /// </summary>
    ENABLE_FILE_ENCRYPTION_RULE = 0x00000008,
    /// <summary>
    /// Allow the file open to access the file's security information.
    /// </summary>
    ALLOW_OPEN_WTIH_ACCESS_SYSTEM_SECURITY = 0x00000010,
    /// <summary>
    /// Allow the file open for read access.
    /// </summary>
    ALLOW_OPEN_WITH_READ_ACCESS = 0x00000020,
    /// <summary>
    /// Allow the file open for write access.
    /// </summary>
    ALLOW_OPEN_WITH_WRITE_ACCESS = 0x00000040,
    /// <summary>
    /// Allow the file open for create new file or overwrite access.
    /// </summary>
    ALLOW_OPEN_WITH_CREATE_OR_OVERWRITE_ACCESS = 0x00000080,
    /// <summary>
    /// Allow the file open for delete.
    /// </summary>
    ALLOW_OPEN_WITH_DELETE_ACCESS = 0x00000100,
    /// <summary>
    /// Allow to read the file data.
    /// </summary>
    ALLOW_READ_ACCESS = 0x00000200,
    /// <summary>
    /// Allow write data to the file.
    /// </summary>
    ALLOW_WRITE_ACCESS = 0x00000400,
    /// <summary>
    /// Allow to query file information.
    /// </summary>
    ALLOW_QUERY_INFORMATION_ACCESS = 0x00000800,
    /// <summary>
    /// Allow to change the file information:file attribute,file size,file name,delete file
    /// </summary>
    ALLOW_SET_INFORMATION = 0x00001000,
    /// <summary>
    /// Allow to rename the file.
    /// </summary>
    ALLOW_FILE_RENAME = 0x00002000,
    /// <summary>
    /// Allow to delete the file.
    /// </summary>
    ALLOW_FILE_DELETE = 0x00004000,
    /// <summary>
    /// Allow to change file size.
    /// </summary>
    ALLOW_FILE_SIZE_CHANGE = 0x00008000,
    /// <summary>
    /// Allow query the file security information.
    /// </summary>
    ALLOW_QUERY_SECURITY_ACCESS = 0x00010000,
    /// <summary>
    /// Allow change the file security information.
    /// </summary>
    ALLOW_SET_SECURITY_ACCESS = 0x00020000,
    /// <summary>
    /// Allow to browse the directory file list.
    /// </summary>
    ALLOW_DIRECTORY_LIST_ACCESS = 0x00040000,
    /// <summary>
    /// Allow the remote access via share folder.
    /// </summary>
    ALLOW_FILE_ACCESS_FROM_NETWORK = 0x00080000,
    /// <summary>
    /// Allow to encrypt the new file if the encryption filter rule is enabled, .
    /// </summary>
    ALLOW_ENCRYPT_NEW_FILE = 0x00100000,
    /// <summary>
    /// Allow the application to read the encrypted files, or it will return encrypted data.
    /// </summary>
    ALLOW_READ_ENCRYPTED_FILES = 0x00200000,
    /// <summary>
    /// Allow the application to create a new file after it opened the protected file.
    /// </summary>
    ALLOW_ALL_SAVE_AS = 0x00400000,
    /// <summary>
    /// Allow copy protected files out of the protected folder if ALLOW_ALL_SAVE_AS is enabled.
    /// </summary>
    ALLOW_COPY_PROTECTED_FILES_OUT = 0x00800000,
    /// <summary>
    /// Allow the file to be executed.
    /// </summary>
    ALLOW_FILE_MEMORY_MAPPED = 0x01000000,
	/// <summary>
    /// If it is not exclude filter rule,the access flag can't be 0, at least you need to include this flag
    /// for filter driver with least access right to the file.
    /// </summary>
    LEAST_ACCESS_FLAG = 0xf0000000,
    /// <summary>
    /// Allow the maximum right access.
    /// </summary>
	ALLOW_MAX_RIGHT_ACCESS	= 0xfffffff0,
	
}AccessFlag;


typedef enum _ConnectionPortType 
{
    ClientMessagePort       = 0, 
    ClientControlPort	    = 1,     

} ConnectionPortType;

typedef enum _EVENT_OUTPUT_TYPE 
{
    OUTPUT_NONE			= 0, 
    OUTPUT_DEBUGGER	    = 1,     
	OUTPUT_EVENTLOG	    = 2,     
	OUTPUT_FILE			= 3,     

} EVENT_OUTPUT_TYPE;

typedef enum _EVENT_LEVEL 
{
    EVENT_LEVEL_NONE		=   0,   // Tracing is not on
	EVENT_LEVEL_CRITICAL    =	1,   // Abnormal exit or termination
	EVENT_LEVEL_ERROR       =	2,   // Severe errors that need logging
	EVENT_LEVEL_WARNING     =	3,   // Warnings such as allocation failure
	EVENT_LEVEL_INFORMATION =	4,   // Includes non-error cases(e.g.,Entry-Exit)
	EVENT_LEVEL_VERBOSE     =	5,   // Detailed traces from intermediate steps

} EVENT_LEVEL;

//the commands from user mode app to the filter driver.
typedef enum _ControlType 
{
	CONTROL_SET_INTEGER_DATA = 1,
	CONTROL_SET_STRING_DATA ,
	CONTROL_REGISTER_REQUEST,
	CONTROL_ADD_FILTER_RULE ,
	CONTROL_REMOVE_FILTER_RULE,
	CONTROL_ADD_EXCLUDED_PID,
	CONTROL_REMOVE_EXCLUDED_PID,
	CONTROL_RESET_CONFIG_DATA,
	CONTROL_GET_FILE_HANDLE,
	CONTROL_CLOSE_FILE_HANDLE,
	CONTROL_ADD_INCLUDED_PID,
	CONTROL_REMOVE_INCLUDED_PID,
	CONTROL_ADD_PROTECTED_PID,
	CONTROL_REMOVE_PROTECTED_PID,
	CONTROL_ADD_BLOCK_SAVEAS_PID,
	CONTROL_REMOVE_BLOCK_SAVEAS_PID,
	CONTROL_ADD_INCLUDE_REG_FILTER_ENTRY,
	CONTROL_ADD_EXCLUDE_REG_FILTER_ENTRY,
	CONTROL_REMOVE_REG_FILTER_ENTRY,
	CONTROL_ADD_PROCESS_FILTER_ENTRY,
	CONTROL_REMOVE_PROCESS_FILTER_ENTRY,
	CONTROL_ADD_PROCESS_FILE_ACCESS_ENTRY,
	CONTROL_REMOVE_PROCESS_FILE_ACCESS_ENTRY,
	CONTROL_MAX_TYPE,       

} ControlType;

// the user mode app sends the integer data to filter driver, this is the index of the integer data.
typedef enum _DataControlId 
{
	FILTER_TYPE_ID = 1,			//The filter driver type.
	EVENT_OUTPUT_TYPE_ID,		//Control send the event output type.
	EVENT_LEVEL_ID,				//Control send event level.
	EVENT_FLAGS_ID,				//Control send the event modules
	CONNECTION_TIMEOUT_ID,		//Control send client connection timout in seconds.
	BOOLEAN_CONFIG_ID,			//All the boolean config data setting
	WAIT_BLOCK_DATA_INTERVAL,	//the interval time in milliseconds to wait for the block data download
	WAIT_BLOCK_DATA_TIMEOUT,	//the timeout in milliseconds to wait for the block data ready
	DIR_CACHE_TIMEOUT,			//the directory cache file list time to live in milliseconds
	MAX_TOTAL_DIR_CACHE_SIZE,   //the total size of the dir info buffer
	DELETE_NO_ACCESS_DIR_INFO_IN_SECONDS,   //delete the directory info if there are no access more than this value.
	MESSAGE_IN_QUEUE_TTL_IN_SECONDS,		//set the message in queue time to live.
	MAX_MESSAGES_IN_QUEUE, //set the maximum messages can be kept in queue.

	MAX_DATA_CONTROL_ID,

} DataControlId;



//this is the boolean data of the user mode app sending to the filter.
//this is the boolean configuration of the filter driver.
typedef enum _BooleanConfig 
{
	/// <summary>
    ///for easetag, if it was true, after the reparsepoint file was opened, it won't restore data back for read and write. 
    /// </summary>
    ENABLE_NO_RECALL_FLAG = 0x00000001,
    /// <summary>
    /// if it is true, the filter driver can't be unloaded.
    /// </summary>
    DISABLE_FILTER_UNLOAD_FLAG = 0x00000002,
    /// <summary>
    /// for virtual file, it will set offline attribute if it is true.
    /// </summary>            
    ENABLE_SET_OFFLINE_FLAG = 0x00000004, 
    /// <summary>
    /// for encryption, it is true, it will use the default IV tag to encrypt the files.
    /// </summary>
    ENABLE_DEFAULT_IV_TAG = 0x00000008, 
    /// <summary>
    /// if it is enabled, it will send the message data to a persistent file, or it will send the event to service right away. 
    /// </summary>
    ENABLE_ADD_MESSAGE_TO_FILE = 0x00000010,
    /// <summary>
    /// the encrypted file's meta data was embeded in the reparse point tag, it is for the previous version 5.0.
    /// </summary>
    ENCRYPT_FILE_WITH_REPARSE_POINT_TAG = 0x00000020,  
    /// <summary>
    /// for encryption rule, get the encryption key and IV from user mode for the encrypted files.
    /// </summary>
    REQUEST_ENCRYPT_KEY_AND_IV_FROM_SERVICE = 0x00000040,  
    /// <summary>
    /// for control filter, if it is enabled, the control filte rulle will be applied in boot time.
    /// </summary>
    ENABLE_PROTECTION_IN_BOOT_TIME = 0x00000080,  
    /// <summary>
    /// for encryption rule, get the encryption key and IV and tag data which will attach to the file.
    /// </summary>
    REQUEST_ENCRYPT_KEY_IV_AND_TAGDATA_FROM_SERVICE = 0x00000100, 
    /// <summary>
    /// if it is enabled, it will send the read/write databuffer to user mode.
    /// </summary>
    ENABLE_SEND_DATA_BUFFER = 0x00000200,      
	/// <summary>
    /// if it is enabled, it will reopen the file when rehydration of the stub file.
    /// </summary>
    ENABLE_REOPEN_FILE_ON_REHYDRATION = 0x00000400,    

} BooleanConfig;

//this is the data structure which send control message to kernel from user mode.
//first it needs to set the control type which shows as above enumeration.
//the second is the control id for integer data.
//the third is the integer data.
typedef struct _CONTROL_DATA 
{
	ULONG		ControlType;
	ULONG		ControlId;
	LONGLONG	IntegerData;
	LONGLONG	IntegerData2;
	ULONG		StringLength1;
	WCHAR		StringData1[MAX_PATH];
	ULONG		StringLength2;
	WCHAR		StringData2[MAX_PATH];
	ULONG		StringLength3;
	WCHAR		StringData3[MAX_PATH];
	ULONG		KeyLength;
	UCHAR		Key[MAX_PATH];
	ULONG		IVLength;
	UCHAR		IV[16];
	
} CONTROL_DATA, *PCONTROL_DATA;

//the file was changed, this is the meta data of the file information.
typedef struct _FILE_CHANGED_DATA 
{
	ULONG		SizeOfEntry;
	ULONG		FileEventType;
	LONGLONG	LastWriteTime;
	ULONG		FileNameLength;
	WCHAR		FileName[1];
	//the whole file name path is appended here.

} FILE_CHANGED_DATA, *PFILE_CHANGED_DATA;


//this is the data structure of the filter driver sending data to the user mode app.
typedef struct _MESSAGE_SEND_DATA 
{
	ULONG			MessageId;
	PVOID			FileObject;
	PVOID			FsContext;
	ULONG			MessageType;	
	ULONG			ProcessId;
    ULONG			ThreadId;   
	LONGLONG		Offset; // read/write offset 
	ULONG			Length; //read/write length
	LONGLONG		FileSize;
	LONGLONG		TransactionTime;
	LONGLONG		CreationTime;
	LONGLONG		LastAccessTime;
	LONGLONG		LastWriteTime;
	ULONG			FileAttributes;
	//The disired access,share access and disposition for Create request.
	ULONG			DesiredAccess;
	ULONG			Disposition;
	ULONG			ShareAccess;
	ULONG			CreateOptions;
	ULONG			CreateStatus;

	//For QueryInformation,SetInformation,Directory request it is information class
	//For QuerySecurity and SetSecurity request,it is securityInformation.
	ULONG			InfoClass; 

	ULONG			Status;
	ULONG			FileNameLength;
	WCHAR			FileName[MAX_FILE_NAME_LENGTH];
	ULONG			SidLength;
    UCHAR			Sid[MAX_SID_LENGTH];
	ULONG			DataBufferLength;
	UCHAR			DataBuffer[BLOCK_SIZE];

	ULONG			VerificationNumber;

} MESSAGE_SEND_DATA, *PMESSAGE_SEND_DATA;


//
//the structure of the new creating process	information
typedef struct _PROCESS_INFO
{
	 /// <summary>
    ///this is the request sequential number. 
    /// </summary>
    ULONG MessageId;
	
	//reserve data
	PVOID	Reserve1;
	PVOID	Reserve2;
    /// <summary>
    ///the process message  type.
    /// </summary>
    ULONG MessageType;
    /// <summary>
    ///the transaction time in UTC of this message.
    /// </summary>
    LONGLONG TransactionTime;
    /// <summary>
    //the current process ID of the process.
    /// </summary>
    ULONG ProcessId;
    /// <summary>
    ///the thread ID of the current operation thread.
    /// </summary>
    ULONG ThreadId;
    /// <summary>
    ///The process ID of the parent process for the new process. Note that the parent process is not necessarily the same process as the process that created the new process.  
    /// </summary>
    ULONG ParentProcessId;
    /// <summary>
    ///  The process ID of the process that created the new process.
    /// </summary>
    ULONG CreatingProcessId;
    /// <summary>
    /// The thread ID of the thread that created the new process.
    /// </summary>
    ULONG CreatingThreadId;
    /// <summary>
    ///An ACCESS_MASK value that specifies the access rights to grant for the handle
    /// </summary>
    ULONG DesiredAccess;
    /// <summary>
    ///The type of handle operation. This member might be one of the following values:OB_OPERATION_HANDLE_CREATE,OB_OPERATION_HANDLE_DUPLICATE
    /// </summary>
    ULONG Operation;
    /// <summary>
    /// A Boolean value that specifies whether the ImageFileName member contains the exact file name that is used to open the process executable file.
    /// </summary>
    ULONG FileOpenNameAvailable;
    /// <summary>
    ///the length of the security identifier.
    /// </summary>
    ULONG SidLength;
    /// <summary>
    ///the security identifier data.
    /// </summary>
    UCHAR Sid[MAX_SID_LENGTH];
    /// <summary>
    /// The length of the image file name.
    /// </summary>
    ULONG ImageFileNameLength;
    /// <summary>
    /// The file name of the executable. If the FileOpenNameAvailable member is TRUE, the string specifies the exact file name that is used to open the executable file. 
    /// If FileOpenNameAvailable is FALSE, the operating system might provide only a partial name.
    /// </summary>
    WCHAR	ImageFileName[MAX_FILE_NAME_LENGTH];
    /// <summary>
    /// The length of the command line.
    /// </summary>
    ULONG CommandLineLength;
    /// <summary>
    /// The command that is used to execute the process.
    /// </summary>
    WCHAR	CommandLine[MAX_FILE_NAME_LENGTH];
	/// <summary>
	///the status which returned from file system.
	/// </summary>
	ULONG Status;    
    /// <summary>
    ///the verification number which verifiys the data structure integerity. 
    /// </summary>
    ULONG VerificationNumber;

} PROCESS_INFO, *PPROCESS_INFO;

//The status return to filter,instruct filter driver what action needs to be done.
typedef enum _FilterStatus 
{
	FILTER_MESSAGE_IS_DIRTY			= 0x00000001, //Set this flag if the reply message need to be processed.
	FILTER_COMPLETE_PRE_OPERATION	= 0x00000002, //Set this flag if complete the pre operation. 
	FILTER_DATA_BUFFER_IS_UPDATED	= 0x00000004, //Set this flag if the databuffer was updated.
	FILTER_BLOCK_DATA_WAS_RETURNED	= 0x00000008, //Set this flag if return read block databuffer to filter.
	FILTER_CACHE_FILE_WAS_RETURNED	= 0x00000010, //Set this flag if the whole cache file was downloaded.
	FILTER_REHYDRATE_FILE_VIA_CACHE_FILE	= 0x00000020, //Set this flag if the whole cache file was downloaded and stub file needs to be rehydrated.

} FilterStatus, *PFilterStatus;

//this is the enumeration of the file I/O events.
typedef enum _FileEventType
{
	FILE_WAS_CREATED				= 0x00000020,
	FILE_WAS_WRITTEN				= 0x00000040,
	FILE_WAS_RENAMED				= 0x00000080,
	FILE_WAS_DELETED				= 0x00000100,
	FILE_SECURITY_CHANGED			= 0x00000200,
	FILE_INFO_CHANGED				= 0x00000400,
	FILE_WAS_READ					= 0x00000800,

} FileEventType, *PFileEventType;


//This is the return data structure from user mode to the filter driver.
typedef struct _MESSAGE_REPLY_DATA 
{
	ULONG		MessageId;
	ULONG		MessageType;	
	ULONG		ReturnStatus;
	ULONG		FilterStatus;
	union {
		struct {
				ULONG		DataBufferLength;
				UCHAR		DataBuffer[BLOCK_SIZE];		
		} Data;
		struct {
				ULONG		SizeOfData;
				struct{
							ULONG		AccessFlag;
							ULONG		IVLength;
							UCHAR		IV[16];
							ULONG		EncryptionKeyLength;
							UCHAR		EncryptionKey[32];	
							ULONG		TagDataLength;
							UCHAR		TagData[1];		
					 }Data;
		} AESData;
		struct {
				ULONG		UserNameLength;
				WCHAR		UserName[1];				
		} UserInfo;
		struct {
				ULONG		FileNameLength;
				WCHAR		FileName[1];				
		} FileInfo;

	}ReplyData;
  
} MESSAGE_REPLY_DATA, *PMESSAGE_REPLY_DATA;


#define STATUS_ACCESS_DENIED				0xC0000022L

extern "C" __declspec(dllexport) 
BOOL
InstallDriver();

extern "C" __declspec(dllexport) 
BOOL
UnInstallDriver();

extern "C" __declspec(dllexport) 
BOOL
SetRegistrationKey(char* key);

typedef BOOL (__stdcall *Proto_Message_Callback)(
   IN		PMESSAGE_SEND_DATA pSendMessage,
   IN OUT	PMESSAGE_REPLY_DATA pReplyMessage);

typedef VOID (__stdcall *Proto_Disconnect_Callback)();

extern "C" __declspec(dllexport) 
BOOL
RegisterMessageCallback(
	ULONG ThreadCount,
	Proto_Message_Callback MessageCallback,
	Proto_Disconnect_Callback DisconnectCallback );

extern "C" __declspec(dllexport) 
VOID
Disconnect();

extern "C" __declspec(dllexport) 
BOOL
GetLastErrorMessage(WCHAR* Buffer, PULONG BufferLength);

extern "C" __declspec(dllexport)
BOOL
SetIntegerData(ULONG dataControlId, LONGLONG data );

extern "C" __declspec(dllexport)
BOOL
SetStringData(ULONG stringControlId, WCHAR* stringData);

extern "C" __declspec(dllexport)
BOOL
ResetConfigData();

extern "C" __declspec(dllexport)  
BOOL
ProtectCurrentProcess();

extern "C" __declspec(dllexport)  
BOOL
StopProtectCurrentProcess();

extern "C" __declspec(dllexport)  
BOOL
SetFilterType(ULONG FilterType);

extern "C" __declspec(dllexport)  
BOOL
SetBooleanConfig(ULONG booleanConfig);

extern "C" __declspec(dllexport)  
BOOL
SetConnectionTimeout(ULONG TimeOutInSeconds);

extern "C" __declspec(dllexport) 
BOOL 
AddFilterRule(ULONG AccessFlag, WCHAR* FilterMask, WCHAR* FilterMask2 = NULL,ULONG keyLength = 0,PUCHAR key = NULL);

extern "C" __declspec(dllexport) 
BOOL 
AddNewFilterRule(ULONG accessFlag, WCHAR* filterMask,BOOL isResident = FALSE);

extern "C" __declspec(dllexport) 
BOOL 
AddFileFilterRule(ULONG accessFlag, WCHAR* filterMask,BOOL isResident = FALSE, ULONG filterRuleId = 0 );

extern "C" __declspec(dllexport) 
BOOL 
AddEncryptionKeyToFilterRule(WCHAR* filterMask,ULONG encryptionKeyLength,PUCHAR encryptionKey);

extern "C" __declspec(dllexport) 
BOOL 
AddEncryptionKeyAndIVToFilterRule(WCHAR* filterMask,ULONG encryptionKeyLength,PUCHAR encryptionKey,ULONG ivLength, PUCHAR iv);

extern "C" __declspec(dllexport) 
BOOL 
AddReparseFileMaskToFilterRule(WCHAR* filterMask,  WCHAR* reparseFilterMask);

extern "C" __declspec(dllexport) 
BOOL 
AddHiddenFileMaskToFilterRule(WCHAR* filterMask,  WCHAR* hiddenFileFilterMask);
extern "C" __declspec(dllexport) 
BOOL 
AddExcludeFileMaskToFilterRule(WCHAR* filterMask,  WCHAR* excludeFileFilterMask);

extern "C" __declspec(dllexport) 
BOOL 
AddExcludeProcessIdToFilterRule(WCHAR* filterMask, ULONG excludePID);

extern "C" __declspec(dllexport) 
BOOL 
AddIncludeProcessIdToFilterRule(WCHAR* filterMask, ULONG includePID);

extern "C" __declspec(dllexport) 
BOOL 
RegisterEventTypeToFilterRule(WCHAR* filterMask, ULONG eventType);

extern "C" __declspec(dllexport) 
BOOL 
RegisterMoinitorIOToFilterRule(WCHAR* filterMask, ULONG registerIO);

extern "C" __declspec(dllexport) 
BOOL 
RegisterControlIOToFilterRule(WCHAR* filterMask, ULONG registerIO);

extern "C" __declspec(dllexport) 
BOOL 
AddRegisterIOFilterToFilterRule(WCHAR* filterMask, ULONG filterByDesiredAccess, ULONG filterByDisposition,ULONG filterByCreateOptions);

extern "C" __declspec(dllexport) 
BOOL 
AddIncludeProcessNameToFilterRule(WCHAR* filterMask,  WCHAR* processName);

extern "C" __declspec(dllexport) 
BOOL 
AddExcludeProcessNameToFilterRule(WCHAR* filterMask,  WCHAR* processName);

extern "C" __declspec(dllexport) 
BOOL 
AddIncludeUserNameToFilterRule(WCHAR* filterMask,  WCHAR* userName);

extern "C" __declspec(dllexport) 
BOOL 
AddExcludeUserNameToFilterRule(WCHAR* filterMask,  WCHAR* processName);

extern "C" __declspec(dllexport) 
BOOL 
AddProcessRightsToFilterRule(WCHAR* filterMask,  WCHAR* processName, ULONG accessFlags);

extern "C" __declspec(dllexport) 
BOOL
RemoveProcessRightsFromFilterRule(WCHAR* filterMask,  WCHAR* processName);

extern "C" __declspec(dllexport) 
BOOL 
AddProcessIdRightsToFilterRule(WCHAR* filterMask,  ULONG processId, ULONG accessFlags);

extern "C" __declspec(dllexport) 
BOOL 
RemoveProcessIdRightsFromFilterRule(WCHAR* filterMask,  ULONG processId);

extern "C" __declspec(dllexport) 
BOOL 
AddUserRightsToFilterRule(WCHAR* filterMask,  WCHAR* userName, ULONG accessFlags);

extern "C" __declspec(dllexport) 
BOOL 
AddBooleanConfigToFilterRule(WCHAR* filterMask, ULONG booleanConfig);

extern "C" __declspec(dllexport) 
BOOL 
RemoveBooleanConfigFromFilterRule(WCHAR* filterMask);

extern "C" __declspec(dllexport) 
BOOL 
RemoveFilterRule(WCHAR* FilterMask);

extern "C" __declspec(dllexport) 
BOOL 
AddExcludedProcessId(ULONG ProcessId);

extern "C" __declspec(dllexport) 
BOOL 
RemoveExcludeProcessId(ULONG ProcessId);

extern "C" __declspec(dllexport)
BOOL 
AddIncludedProcessId(ULONG processId);

extern "C" __declspec(dllexport) 
BOOL 
RemoveIncludeProcessId(ULONG processId);

extern "C" __declspec(dllexport)
BOOL 
AddProtectedProcessId(ULONG processId);

extern "C" __declspec(dllexport) 
BOOL 
RemoveProtectedProcessId(ULONG processId);

extern "C" __declspec(dllexport)
BOOL 
AddBlockSaveAsProcessId(ULONG processId);

extern "C" __declspec(dllexport) 
BOOL 
RemoveBlockSaveAsProcessId(ULONG processId);

extern "C" __declspec(dllexport) 
BOOL 
RegisterIoRequest(ULONG RequestRegistration);

extern "C" __declspec(dllexport) 
BOOL	
GetFileHandleInFilter(WCHAR* FileName,ULONG  DesiredAccess,HANDLE*	FileHandle);

extern "C" __declspec(dllexport) 
BOOL
CloseFileHandleInFilter(HANDLE hFile);

extern "C" __declspec(dllexport) 
BOOL
IsDriverServiceRunning();

extern "C" __declspec(dllexport) 
BOOL
OpenStubFile(
    LPCTSTR fileName,
    DWORD   dwDesiredAccess,
    DWORD   dwShareMode,
    PHANDLE pHandle );

extern "C" __declspec(dllexport) 
BOOL
CreateFileAPI(
	LPCTSTR		fileName,
	DWORD		dwDesiredAccess,
	DWORD		dwShareMode,
	DWORD		dwCreationDisposition,
	DWORD		dwFlagsAndAttributes,
	PHANDLE		pHandle );

extern "C" __declspec(dllexport) 
BOOL
CreateStubFile(
	LPCTSTR		fileName,
	LONGLONG	fileSize,
	ULONG		fileAttributes,
	ULONG		tagDataLength,
	BYTE*		tagData,
	BOOL		overwriteIfExist,
	PHANDLE		pHandle );

extern "C" __declspec(dllexport) 
BOOL
GetTagData(
	HANDLE hFile,
	PULONG tagDataLength,
	BYTE*  tagData);

extern "C" __declspec(dllexport) 
BOOL  
RemoveTagData(
    HANDLE hFile ,
	BOOLEAN	updateTimeStamp = FALSE);

extern "C" __declspec(dllexport) 
BOOL 
AddTagData(
    HANDLE  hFile, 
    ULONG   tagDataLength,
	BYTE*	tagData );

extern "C" __declspec(dllexport) 
BOOL 
AddReparseTagData(
	LPCTSTR		fileName,
    ULONG		tagDataLength,
	BYTE*		tagData );

extern "C" __declspec(dllexport) 
BOOL  
QueryAllocatedRanges(
    IN HANDLE							hFile, 
    IN LONGLONG                         queryOffset,
    IN LONGLONG                         queryLength,
    IN OUT PFILE_ALLOCATED_RANGE_BUFFER allocatedBuffer,
    IN ULONG                            allocatedBufferSize,   
    OUT ULONG                           *returnBufferLength  );

extern "C" __declspec(dllexport) 
BOOL
SetFileSize(
	HANDLE			hFile,
	LONGLONG		fileSize);

extern "C" __declspec(dllexport) 
BOOL
AESEncryptFile(
	LPCTSTR					fileName,
	ULONG					keyLength,
	BYTE*					key,
	ULONG					ivLength = 0,
	BYTE*					iv = NULL,
	BOOLEAN					addAESData = TRUE);

extern "C" __declspec(dllexport) 
BOOL
AESDecryptFile(
	LPCTSTR		fileName,
	ULONG		keyLength,
	BYTE*		key,
	ULONG		ivLength = 0,
	BYTE*		iv = NULL);

extern "C" __declspec(dllexport) 
BOOL
AESEncryptFileToFileWithTag(
	LPCTSTR					sourceFileName,
	LPCTSTR					destFileName,
	ULONG					keyLength,
	BYTE*					key,
	ULONG					ivLength,
	BYTE*					iv,
	ULONG					tagDataLength,
	BYTE*					tagData );

extern "C" __declspec(dllexport) 
BOOL
AESEncryptFileWithTag(
	LPCTSTR					fileName,
	ULONG					keyLength,
	BYTE*					key,
	ULONG					ivLength,
	BYTE*					iv,
	ULONG					tagDataLength,
	BYTE*					tagData );

extern "C" __declspec(dllexport) 
BOOL
AESEncryptFileToFile(
	LPCTSTR					sourceFileName,
	LPCTSTR					destFileName,
	ULONG					keyLength,
	BYTE*					key,
	ULONG					ivLength,
	BYTE*					iv,
	BOOLEAN					addAESData );

extern "C" __declspec(dllexport) 
BOOL
AESDecryptFileWithKey(
	LPCTSTR		fileName,
	ULONG		keyLength,
	BYTE*		key );

extern "C" __declspec(dllexport) 
BOOL
AESDecryptFileToFile(
	LPCTSTR					sourceFileName,
	LPCTSTR					destFileName,
	ULONG					keyLength,
	BYTE*					key,
	ULONG					ivLength = 0,
	BYTE*					iv = NULL);
 
extern "C" __declspec(dllexport) 
BOOL
AESEncryptDecryptBuffer(
	BYTE*					inputBuffer,
	BYTE*					outputBuffer,
	ULONG					bufferLength,
	LONGLONG				offset,
	BYTE*					key,
	ULONG					keyLength,
	BYTE*					ivKey,
	ULONG					ivLength);

extern "C" __declspec(dllexport) 
BOOL
GetUniqueComputerId(
	BYTE*					buffer,
	PULONG					bufferLength  );

extern "C" __declspec(dllexport) 
BOOL
ActivateLicense(
	BYTE*					buffer,
	ULONG					bufferLength);


extern "C" __declspec(dllexport) 
BOOL
AddRegistryFilterRule(
	ULONG		prcoessNameLength,
	WCHAR*		processNameFilterMask, 
	ULONG		processId,
	ULONG		userNameLength,
	WCHAR*		userNameFilterMask, 
	ULONG		keyNameLength,
	WCHAR*		keyNameFilterMask, 
	ULONG		accessFlag,
	ULONGLONG	regCallbackClass,
	BOOL		isExcludeFilter );

extern "C" __declspec(dllexport) 
BOOL
AddRegistryFilterRuleByProcessName(
	ULONG		prcoessNameLength,
	WCHAR*		processName, 
	ULONG		accessFlag,
	ULONGLONG	regCallbackClass,
	BOOL		isExcludeFilter );

extern "C" __declspec(dllexport) 
BOOL
AddRegistryFilterRuleById(
	ULONG		processId,
	ULONG		accessFlag,
	ULONGLONG	regCallbackClass,
	BOOL		isExcludeFilter );

extern "C" __declspec(dllexport) 
BOOL
RemoveRegFilterEntryByProcessId(
	ULONG		processId );

extern "C" __declspec(dllexport) 
BOOL
RemoveRegFilterEntryByProcessName(
	ULONG		prcoessNameLength,
	WCHAR*		processName );

extern "C" __declspec(dllexport) 
BOOL
AddProcessFilterRule(	
	ULONG		prcoessNameMaskLength,
	WCHAR*		processNameMask,
	ULONG		controlFlag,
	ULONG		filterRuleId = 0 );

extern "C" __declspec(dllexport) 
BOOL
RemoveProcessFilterRule(
	ULONG		prcoessNameMaskLength,
	WCHAR*		processNameMask );

extern "C" __declspec(dllexport) 
BOOL
RegisterIOToProcessName(
	ULONG  processNameMaskLength,
	WCHAR* processNameMask,
	ULONG  monitorIOs,
	ULONG  controlIOs);

extern "C" __declspec(dllexport) 
BOOL
AddFileControlToProcessByName(	
	ULONG		prcoessNameMaskLength,
	WCHAR*		processNameMask,
	ULONG		fileNameMaskLength,
	WCHAR*		fileNameMask,
	ULONG		AccessFlag );

extern "C" __declspec(dllexport) 
BOOL
AddFileCallbackIOToProcessByName(	
	ULONG		prcoessNameMaskLength,
	WCHAR*		processNameMask,
	ULONG		fileNameMaskLength,
	WCHAR*		fileNameMask,
	ULONG		monitorIOs,
	ULONG		controlIOs,
	ULONG		filterByDesiredAccess,
    ULONG		filterByDisposition,
    ULONG		filterByCreateOptions);

extern "C" __declspec(dllexport) 
BOOL
RemoveFileControlFromProcessByName(	
	ULONG		prcoessNameMaskLength,
	WCHAR*		processNameMask,
	ULONG		fileNameMaskLength,
	WCHAR*		fileNameMask);

extern "C" __declspec(dllexport) 
BOOL
AddFileControlToProcessById(	
	ULONG		prcoessId,
	ULONG		fileNameMaskLength,
	WCHAR*		fileNameMask,
	ULONG		AccessFlag );

extern "C" __declspec(dllexport) 
BOOL
RemoveFileControlFromProcessById(	
	ULONG		prcoessId,
	ULONG		fileNameMaskLength,
	WCHAR*		fileNameMask);

extern "C" __declspec(dllexport) 
BOOL
SetAESVersion(ULONG version);

extern "C" __declspec(dllexport) 
BOOL
SetAESHeaderSize(ULONG headerSize);

extern "C" __declspec(dllexport) 
BOOL
EnableReparsePointTagEncryption();

extern "C" __declspec(dllexport) 
BOOL
AddAESHeader(
	LPCTSTR		fileName,
	ULONG		headerSize,
	BYTE*		header);

extern "C" __declspec(dllexport) 
BOOL
GetAESHeader(
	LPCTSTR		fileName,
	PULONG		headerSize,
	BYTE*		header);

extern "C" __declspec(dllexport) 
BOOL
SetHeaderFlags(
 	LPCTSTR		fileName,
	ULONG		aesFlags,
	ULONG		accessFlags );

extern "C" __declspec(dllexport) 
BOOL
GetAESTagData(
	LPCTSTR		fileName,
	PULONG		tagDataSize,
	BYTE*		tagData);

#endif//__SHARE_TYPE_H__
