#ifndef _DBO_TSMAIN_H_
#define _DBO_TSMAIN_H_


//#include "DboTSCoreDefine.h"
#include "NtlTSMain.h"
#include "NtlTSRTTI.h"

class CDboTSEntityFactory;
class CDboTSCtrlFactory;
class CDboTSUIFactory;
class CDboTSQAgency;
class CDboTSQRecv;
class CNtlUnzip;
class CNtlTSMain;
class CNtlTSRTTI;


/** 
	Trigger system main
	���� : Ʈ���� �ý��ۿ��� ���������� ���Ǵ� ���ҽ��� �����ϸ�
		   Trigger agency �� ���� ���� �� �Ҹ��� ����Ѵ�
*/


class CDboTSMain : public CNtlTSMain
{
	NTL_TS_DECLARE_RTTI(CDboTSMain, CNtlTSMain)
/*public:
	static	const CNtlTSRTTI	RTTI; 
	virtual	const CNtlTSRTTI&	GetRTTI(void)	const { return RTTI; } 
	const char*			GetClassName(void) const { return GetRTTI().GetClassName(); } 
	bool				IsSameClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsSameClass(clVal); } 
	bool				IsDerivedClass(const CNtlTSRTTI& clVal) const { return GetRTTI().IsDerivedClass(clVal); } 
	bool				IsDerivedClass(const std::string& strClassName) const { return GetRTTI().IsDerivedClass(strClassName); }*/

// Declarations
public:
	//typedef stdext::hash_map<std::string, CNtlTSEvtMapper*> hashdef_EVT_MAPPER_LIST;

// Member variables
protected:
	// Log
	//CNtlTSLog*							m_pLog;

	// Factories
	CDboTSEntityFactory*				m_pEntityFactory;
	CDboTSCtrlFactory*					m_pCtrlFactory;
	//CDboTSUIFactory*					m_pUIFactory;

	// Event mapper
//	hashdef_EVT_MAPPER_LIST				m_defEvtMapper;

// Constructions and Destructions
public:
	CDboTSMain( void );
	virtual ~CDboTSMain( void );

// Methods
public:
	virtual bool						Create(void);
	virtual void						Delete( void );

	/*CDboTSEntityFactory*				GetEntityFactory( void );
	CDboTSCtrlFactory*					GetControlFactory( void );
	CDboTSUIFactory*					GetUIFactory( void );

	hashdef_EVT_MAPPER_LIST&			GetEventMapper( void );
	CNtlTSEvtMapper*					FindEventMapper( const std::string& strMapper );

	void								DeleteAgency( CNtlTSAgency*& pTSAgency );*/

// Implementations
protected:
	//virtual bool						LoadLog( void );
	//virtual void						UnloadLog( void );

	virtual bool						LoadFactories( void );
	virtual void						UnloadFactories( void );

	virtual bool						LoadScripts( void );
	virtual void						UnloadAllScripts( void );

	virtual bool						LoadEventMappers( void );
	virtual void						UnloadEventMappers( void );

	virtual bool						LoadRecv( void );
	virtual void						UnloadRecv( void );

	// ������ ������ ������ ���� �����鿡 ���� TS ����( .t )���� �ε��Ѵ�
	bool								LoadTSPath( std::string strPath, mapdef_TLIST& defTList );
	// Zip ���Ͼ��� TS ����( .t )���� �ε��Ѵ�
	/*bool								LoadTSZip( std::string strFile, mapdef_TLIST& defTList );
	// ��ȣȭ�� Zip ���Ͼ��� TS ����( .t )���� �ε��Ѵ�
	bool								LoadTSCryptoData( std::string strFile, mapdef_TLIST& defTList );
	// ��ȣȭ�� ���Ͼ��� Zip ������ �ε��Ѵ�
	bool								LoadTSCryptoData_UnZip( std::string strFile, CNtlUnzip* pclUnzip );

	bool								LoadTriggerObject( const std::string& strPath, const char* pFileName, mapdef_TLIST& defTList );
	bool								LoadTriggerObject( const std::string& strPath, const char* pFileName, char* pBuff, int nSize, mapdef_TLIST& defTList );
	bool								LoadTriggerObjectFromUnZip( NTL_TS_T_ID tID, CNtlUnzip* pclUnzip, mapdef_TLIST& defTList );*/
};


/*inline CDboTSEntityFactory* CDboTSMain::GetEntityFactory( void )
{
	return m_pEntityFactory;
}

inline CDboTSCtrlFactory* CDboTSMain::GetControlFactory( void )
{
	return m_pCtrlFactory;
}

inline CDboTSUIFactory* CDboTSMain::GetUIFactory( void )
{
	return m_pUIFactory;
}*/


#endif