
struct raytrace
{
	VectorAligned	m_Start;
	VectorAligned	m_Delta;
	VectorAligned	m_StartOffset;
	VectorAligned	m_Extents;
	bool			m_IsRay;
	bool			m_IsSwept;

	void Init(Vector start, Vector end)
	{
		m_Delta.x = end.x - start.x;
		m_Delta.y = end.y - start.y;
		m_Delta.z = end.z - start.z;
		m_Extents.x = m_Extents.y = m_Extents.z = 0;
		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0;
		m_Start.x = start.x;
		m_Start.y = start.y;
		m_Start.z = start.z;

		m_IsRay = 1;
		m_IsSwept = m_Delta.length_sqr() != 0;
	}
};

struct tracefitlers
{
	tracefitlers(const CBaseEntity* entity) : skip{ entity } { }
	virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		CBaseEntity *pEntity = (CBaseEntity *)pEntityHandle;

		if (ClientClass* cl = pEntity->GetClientClass())
		{
			const char* cclass = cl->GetName;

			if (!strcmp(cclass, "CFuncNewTeamWall"))
				return 0;
		}

		return !(pEntityHandle == skip);
	}
	virtual int getTraceType() const { return 0; }
	const void* skip;
};

struct cplane_t
{
	Vector normal;
	float dist;
	BYTE type;
	BYTE signBits;
	BYTE pad[2];
};

struct csurface_t
{
	const char*		name;
	short			surfaceProps;
	unsigned short	flags;
};

struct traceclass
{
	Vector	start;
	Vector	endpos;
	cplane_t	plane;
	float		fraction;
	int			contents;
	WORD		dispFlags;
	bool		allSolid;
	bool		startSolid;
	float		fractionLeftSolid;
	csurface_t	surface;
	int			hitgroup;
	short		physicsBone;
	CBaseEntity* entity;
	int			hitbox;
};

class CEnginetrace
{
public:
	__forceinline void TraceRay(const raytrace& ray, uint32_t mask, tracefitlers* filter, traceclass* trace)
	{
		return getvfunc< void(__thiscall*)(decltype(this), const raytrace&, uint32_t, tracefitlers*, traceclass*) >(this, 4)(this, ray, mask, filter, trace);
	}
};

