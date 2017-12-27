namespace network
{	
	enum messageHeader //single byte
	{
		NO_TRAFFIC,

		SEND_IDS,
		PING_ID,
		PING_REPLY,
		MY_ID,

		REGISTER_MY_ID,
		REGISTER_REQ_KEY,
		REGISTER_MY_KEY,
		REGISTER_ACCEPT,
		REGISTER_DENY,

		SEND_TO_ALL,
		SEND_TO_ID
	};
}
