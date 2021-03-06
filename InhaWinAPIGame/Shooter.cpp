#include "Shooter.h"

#include "MathSH.h"

Shooter::Shooter( const Vec2<float>& size, const Vec2<float>& frameSize )
	:
	pImage( ImageCodex::Retrieve( imagename ) ),
	size( size ),
	frameSize(frameSize)
{
}

void Shooter::Update( float dt, Scene& scene )
{
	angle = MathSH::WrapAngle( angle );
	
	const Vec2<float> topPos = { center.x, center.y - size.y };
	shootPos = (topPos - rotateCenter).Rotate( angle * MathSH::PI / 180.0f ) + rotateCenter;
	
	KbdInput( dt );
}

void Shooter::Draw( HDC hdc )
{
	surface.DrawImageChroma( hdc, pImage.get(), {center.x - size.x, center.y - size.y},
		{ center.x + size.x, center.y + size.y }, { 0,0 }, imageEnd, rotateCenter, angle );

	surface.DrawArc( hdc, Gdiplus::Color( 255, 87, 111, 139 ), 50,
		{ rotateCenter.x - frameSize.x * 0.5f, rotateCenter.y, frameSize.x, frameSize.y },
		0, -180 );
}

void Shooter::SetCenter( const Vec2<float>& v )
{
	center = v;
}

void Shooter::SetRotateCenter( const Vec2<float>& v )
{
	rotateCenter = v;
}

Vec2<float> Shooter::GetShootPos() const
{
	return shootPos;
}

Vec2<float> Shooter::GetShootDir() const
{
	return (shootPos - rotateCenter).Normalize();
}

void Shooter::SetStateFireCooldown()
{
	state = State::FireCooldown;
}

 Shooter::State Shooter::GetState()
{
	return state;
}

void Shooter::KbdInput( float dt )
{
	fireTime += dt;

	if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
	{
		angle += rotateSpeed * dt;
		if ( angle >= 60.0f )
		{
			angle = 60.0f;
		}
	}
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
	{
		angle -= rotateSpeed * dt;
		if ( angle <= -60.0f )
		{
			angle = -60.0f;
		}
	}
}
