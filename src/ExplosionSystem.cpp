#include "ExplosionSystem.h"
#include "ElapsedTime.h"


	ExplosionSystem::ExplosionSystem()
	{
	}

	ExplosionSystem::~ExplosionSystem()
	{
	}

	void ExplosionSystem::setCamera(PivotCamera *camera)
	{
		this->camera = camera;
	}


	void ExplosionSystem::Render()
	{
		for (auto it = MistVector.begin(); it != MistVector.end(); it++)
			it->first.Render();

		for (auto it = BurstVector.begin(); it != BurstVector.end(); it++)
			it->first.Render();

		for (auto it = ShockwaveVector.begin(); it != ShockwaveVector.end(); it++)
			it->first.Render();

		for (auto it = FlashVector.begin(); it != FlashVector.end(); it++)
			it->first.Render();

		for (auto it = SparksVector.begin(); it != SparksVector.end(); it++)
			it->first.Render();

		for (auto it = TrailSystemVector.begin(); it != TrailSystemVector.end(); it++)
		 	it->Render();

		for (auto it = DebrisVector.begin(); it != DebrisVector.end(); it++)
			it->first.Render();

	}

	void ExplosionSystem::BuildVertexBuffer()
	{
		for (auto it = MistVector.begin(); it != MistVector.end(); it++)
			it->first.BuildVertexBuffer();

		for (auto it = BurstVector.begin(); it != BurstVector.end(); it++)
			it->first.BuildVertexBuffer();

		for (auto it = ShockwaveVector.begin(); it != ShockwaveVector.end(); it++)
			it->first.BuildVertexBuffer();

		for (auto it = FlashVector.begin(); it != FlashVector.end(); it++)
			it->first.BuildVertexBuffer();

		for (auto it = SparksVector.begin(); it != SparksVector.end(); it++)
			it->first.BuildVertexBuffer();

		for (auto it = TrailSystemVector.begin(); it != TrailSystemVector.end(); it++)
			it->BuildVertexBuffer();

		for (auto it = DebrisVector.begin(); it != DebrisVector.end(); it++)
			it->first.BuildVertexBuffer();

	}

	void ExplosionSystem::Update(float fDeltaTime)
	{
		int i = 0;

		for (auto it = MistVector.begin(); it != MistVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				MistVector.erase(MistVector.begin() + i);
		}

		i = 0;

		for (auto it = BurstVector.begin(); it != BurstVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				BurstVector.erase(BurstVector.begin() + i);
		}

		i = 0;

		for (auto it = ShockwaveVector.begin(); it != ShockwaveVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				ShockwaveVector.erase(ShockwaveVector.begin() + i);
		}

		i = 0;

		for (auto it = FlashVector.begin(); it != FlashVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				FlashVector.erase(FlashVector.begin() + i);
		}

		i = 0;

		for (auto it = SparksVector.begin(); it != SparksVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				SparksVector.erase(SparksVector.begin() + i);
		}

		i = 0;

		for (auto it = TrailSystemVector.begin(); it != TrailSystemVector.end();)
		{
			if (it->Active())
			{
				it->Update(fDeltaTime);
				it++;
				i++;
			}
			else
				TrailSystemVector.erase(TrailSystemVector.begin() + i);
		}

		i = 0;

		for (auto it = DebrisVector.begin(); it != DebrisVector.end();)
		{
			if (it->first.Active())
			{
				it->first.Update(fDeltaTime);
				it++;
				i++;
			}
			else
				DebrisVector.erase(DebrisVector.begin() + i);
		}
	
	}

	void ExplosionSystem::addExplosion(glm::vec3 origin)
	{
		MistEffect *g_MistEffect = new MistEffect(150);
		MistEmitter *g_MistEmitter = new MistEmitter();

		BurstEffect *g_BurstEffect = new BurstEffect(40);
		BurstEmitter *g_BurstEmitter = new BurstEmitter();

		ShockwaveEffect *g_ShockwaveEffect = new ShockwaveEffect(1);
		ShockwaveEmitter *g_ShockwaveEmitter = new ShockwaveEmitter();

		FlashEffect *g_FlashEffect = new FlashEffect(5);
		FlashEmitter *g_FlashEmitter = new FlashEmitter();

		ExplosionSparksEffect *g_ExplosionSparksEffect = new ExplosionSparksEffect(40);
		ExplosionSparksEmitter *g_ExplosionSparksEmitter = new ExplosionSparksEmitter();

		DebrisEffect *g_DebrisEffect = new DebrisEffect(25);
		DebrisEmitter *g_DebrisEmitter = new DebrisEmitter();

		TrailSystem *g_TrailSystem = new TrailSystem(15, origin);


		g_MistEmitter->setOrigin(origin);
		g_BurstEmitter->setOrigin(origin);
		g_ShockwaveEmitter->setOrigin(origin);
		g_FlashEmitter->setOrigin(origin);
		g_ExplosionSparksEmitter->setOrigin(origin);
		g_DebrisEmitter->setOrigin(origin);

		std::pair <MistEffect, MistEmitter> p1 (*g_MistEffect, *g_MistEmitter);
		std::pair <BurstEffect, BurstEmitter> p2 (*g_BurstEffect, *g_BurstEmitter);
		std::pair <ShockwaveEffect, ShockwaveEmitter> p3 (*g_ShockwaveEffect, *g_ShockwaveEmitter);
		std::pair <FlashEffect, FlashEmitter> p4 (*g_FlashEffect, *g_FlashEmitter);
		std::pair <ExplosionSparksEffect, ExplosionSparksEmitter> p5 (*g_ExplosionSparksEffect, *g_ExplosionSparksEmitter);
		std::pair <DebrisEffect, DebrisEmitter> p6 (*g_DebrisEffect, *g_DebrisEmitter);

		MistVector.push_back(p1);
		BurstVector.push_back(p2);
		ShockwaveVector.push_back(p3);
		FlashVector.push_back(p4);
		SparksVector.push_back(p5);
		DebrisVector.push_back(p6);

		g_TrailSystem->setCamera(camera);
		g_TrailSystem->addTrails();
		TrailSystemVector.push_back(*g_TrailSystem);
	}

	void ExplosionSystem::setExplosion()
	{
		setMist();
		setBurst();
    	setFlash();
    	setTrails();
    	setShockwave();
    	setExplosionSparks();
    	setDebris();
	}

	void ExplosionSystem::setMist()
	{
		MistEffect *g_MistEffect = nullptr;
		MistEmitter *g_MistEmitter = nullptr;

		if (MistVector.size() != 0)
		{
			g_MistEffect = &MistVector[MistVector.size() - 1].first; 
			g_MistEmitter = &MistVector[MistVector.size() - 1].second;
		}

		g_MistEffect->LoadTexture("./Textures/smoke/smoke2.png");
		
       
    	MistEffect::ColorInterpolator mistcolors;

    	mistcolors.AddValue(0.0f, glm::vec4(0.13, 0.13, 0.13, 0.00));
    	mistcolors.AddValue(0.15f, glm::vec4(0.13, 0.13, 0.13, 0.0));
    	mistcolors.AddValue(0.2f, glm::vec4(0.13, 0.13, 0.13, 0.15));
    	mistcolors.AddValue(0.9f, glm::vec4(0.13, 0.13, 0.13, 0.0));

    	g_MistEffect->SetColorInterplator(mistcolors);
    	g_MistEffect->SetParticleEmitter(g_MistEmitter);
    	g_MistEffect->EmitParticles();
    	g_MistEffect->SetCamera(camera);
	}

	void ExplosionSystem::setBurst()
	{
		BurstEffect *g_BurstEffect = nullptr;
		BurstEmitter *g_BurstEmitter = nullptr;

		if (BurstVector.size() != 0)
		{
			g_BurstEffect = &BurstVector[BurstVector.size() - 1].first; 
			g_BurstEmitter = &BurstVector[BurstVector.size() - 1].second;
		}

    	g_BurstEffect->LoadTexture("./Textures/fire/fire1.png");

    	BurstEffect::ColorInterpolator burstColors;
    	
    	burstColors.AddValue(0.01f, glm::vec4(1, 1, 1, 1));
    	burstColors.AddValue(0.05f, glm::vec4(1, 1, 0.9, 0.5));
    	burstColors.AddValue(0.2f, glm::vec4(1, 0.64, 0, 0.5));
    	burstColors.AddValue(0.21f, glm::vec4(1, 0.54, 0.0, 0.5));
    	burstColors.AddValue(0.9f, glm::vec4(0.13, 0.13, 0.13, 0));

    	g_BurstEffect->SetColorInterplator(burstColors);
    	g_BurstEffect->SetParticleEmitter(g_BurstEmitter);
    	g_BurstEffect->EmitParticles();
    	g_BurstEffect->SetCamera(camera);  
	}

	void ExplosionSystem::setShockwave()
	{
		ShockwaveEffect *g_ShockwaveEffect = nullptr;
		ShockwaveEmitter *g_ShockwaveEmitter = nullptr;

		if (ShockwaveVector.size() != 0)
		{
			g_ShockwaveEffect = &ShockwaveVector[ShockwaveVector.size() - 1].first; 
			g_ShockwaveEmitter = &ShockwaveVector[ShockwaveVector.size() - 1].second;
		}


    g_ShockwaveEffect->LoadTexture("./Textures/shockwave/shockwave.png");

    ShockwaveEffect::ColorInterpolator shockwaveColors;

    shockwaveColors.AddValue(0.01f, glm::vec4(0.8, 0.2, 0.0, 1));
    shockwaveColors.AddValue(0.75f, glm::vec4(0.8, 0.2, 0.0, 0.2));
    shockwaveColors.AddValue(0.75f, glm::vec4(0.1, 0.1, 0.1, 0));

    g_ShockwaveEffect->SetColorInterplator(shockwaveColors);
    g_ShockwaveEffect->SetParticleEmitter(g_ShockwaveEmitter);
    g_ShockwaveEffect->EmitParticles(); 
    //g_ShockwaveEffect.SetCamera(camera);   
	}

	void ExplosionSystem::setFlash()
	{
		FlashEffect *g_FlashEffect = nullptr;
		FlashEmitter *g_FlashEmitter = nullptr;

		if (FlashVector.size() != 0)
		{
			g_FlashEffect = &FlashVector[FlashVector.size() - 1].first; 
			g_FlashEmitter = &FlashVector[FlashVector.size() - 1].second;
		}


   		g_FlashEffect->LoadTexture("./Textures/flashs/flash2.png");
        
    	FlashEffect::ColorInterpolator flashColors;

    	flashColors.AddValue(0.05f, glm::vec4(1, 1, 1, 0.8));
    	flashColors.AddValue(0.07f, glm::vec4(1, 1, 0.9, 0.5));
    	flashColors.AddValue(0.75f, glm::vec4(0.1, 0.1, 0.1, 0.0));

    	g_FlashEffect->SetColorInterplator(flashColors);
    	g_FlashEffect->SetParticleEmitter(g_FlashEmitter);
    	g_FlashEffect->EmitParticles();
    	g_FlashEffect->SetCamera(camera); 
	} 

	void ExplosionSystem::setTrails()
	{
		if (TrailSystemVector.size() != 0)
			TrailSystemVector[TrailSystemVector.size() -1].setTrails();
	}

	void ExplosionSystem::setExplosionSparks()
	{
		ExplosionSparksEffect *g_ExplosionSparksEffect = nullptr;
		ExplosionSparksEmitter *g_ExplosionSparksEmitter = nullptr;

		if (SparksVector.size() != 0)
		{
			g_ExplosionSparksEffect = &SparksVector[SparksVector.size() - 1].first; 
			g_ExplosionSparksEmitter = &SparksVector[SparksVector.size() - 1].second;
		}


 		g_ExplosionSparksEffect->LoadTexture("./Textures/roundsparks/roundspark.png");

    	ExplosionSparksEffect::ColorInterpolator explosionSparksColors;

    	explosionSparksColors.AddValue(0.0f, glm::vec4(0.8, 0.2, 0.0, 0.5));
    	explosionSparksColors.AddValue(0.05f, glm::vec4(0.8, 0.2, 0.0, 1));
    	explosionSparksColors.AddValue(0.2f, glm::vec4(1, 0.2, 0, 0.5));
    	explosionSparksColors.AddValue(1.f, glm::vec4(0.12, 0.12, 0.12, 0.0));

    	g_ExplosionSparksEffect->SetColorInterplator(explosionSparksColors);
    	g_ExplosionSparksEffect->SetParticleEmitter(g_ExplosionSparksEmitter);
    	g_ExplosionSparksEffect->EmitParticles();
    	g_ExplosionSparksEffect->SetCamera(camera);
	}

	void ExplosionSystem::setDebris()
	{
		DebrisEffect *g_DebrisEffect = nullptr; 
		DebrisEmitter *g_DebrisEmitter = nullptr;

		if (DebrisVector.size() != 0)
		{
			g_DebrisEffect = &DebrisVector[DebrisVector.size() - 1].first; 
			g_DebrisEmitter = &DebrisVector[DebrisVector.size() - 1].second;
		}		

    	g_DebrisEffect->LoadTexture("./Textures/debris/debris9.png");

	    DebrisEffect::ColorInterpolator debrisColors;

	    debrisColors.AddValue(0.05f, glm::vec4(0.5, 0.5, 0.5, 1));
    	debrisColors.AddValue(0.1f, glm::vec4(1, 1, 1, 1));
    	debrisColors.AddValue(1.f, glm::vec4(0.12, 0.12, 0.12, 0.0));

    	g_DebrisEffect->SetColorInterplator(debrisColors);
    	g_DebrisEffect->SetParticleEmitter(g_DebrisEmitter);
    	g_DebrisEffect->EmitParticles();
    	g_DebrisEffect->SetCamera(camera);  
	}