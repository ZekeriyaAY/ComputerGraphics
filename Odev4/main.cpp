#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

/* Ba�lang�� g�sterim penceresi boyutu */
GLsizei pencereEni = 500, pencereBoyu = 500;

class wcPt3d{
public:
	GLfloat x, y, z;
};

static void init(void)
{
	// Beyaz g�sterim penceresi.
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void noktaCiz(wcPt3d bezierEgriNoktasi){
	glBegin(GL_POINTS);
		glVertex2f(bezierEgriNoktasi.x, bezierEgriNoktasi.y);
	glEnd();
}
/* Verilen n de�erine g�re C binomyal katsay�lar�n� hesaplar. */
void binomyalKatsayilar(GLint n, GLint* C){
	GLint k, j;

	for (k = 0; k <= n; k++){
		/* n!/(k!*(n-k)!) hesab� */
		C[k] = 1;
		for (j = n; j >= k+1; j--)
			C[k] *= j;
		for (j = n-k; j >= 2; j--)
			C[k] /= j;
	}
}
void bezierNoktasiHesapla(GLfloat u, wcPt3d* bezierNoktasi, GLint kontrolNoktasiSayisi, wcPt3d* kontrolNoktalari, GLint *C){
	GLint k, n = kontrolNoktasiSayisi-1;
	GLfloat bezierTabanFonksiyonu;
	bezierNoktasi->x = bezierNoktasi->y = bezierNoktasi->z = 0.0;
	/* Taban fonksiyonlar�n� hesapla ve kontrol noktalar�n� harmanla */
	for (k = 0; k < kontrolNoktasiSayisi; k++){
		bezierTabanFonksiyonu = C[k] * (GLfloat) pow(u, k) * (GLfloat) pow(1 - u, n - k);
		bezierNoktasi->x += kontrolNoktalari[k].x * bezierTabanFonksiyonu;
		bezierNoktasi->y += kontrolNoktalari[k].y * bezierTabanFonksiyonu;
		bezierNoktasi->z += kontrolNoktalari[k].z * bezierTabanFonksiyonu;
	}
}

void bezier(GLint kontrolNoktasiSayisi, wcPt3d* kontrolNoktalari, GLint BezierEgrisiNoktaSayisi){
	wcPt3d bezierEgrisiNoktasi;
	GLfloat u;
	GLint *C, k;
	/* Binomyal katsay�lar ii�in alan ay�r. */
	C = new GLint[kontrolNoktasiSayisi];
	binomyalKatsayilar(kontrolNoktasiSayisi-1, C);

	for (k = 0; k <= BezierEgrisiNoktaSayisi; k++){
		u = GLfloat(k) / GLfloat(BezierEgrisiNoktaSayisi);
		bezierNoktasiHesapla(u, &bezierEgrisiNoktasi, kontrolNoktasiSayisi, kontrolNoktalari, C);
		noktaCiz(bezierEgrisiNoktasi);
	}
	delete[] C;
}

void gosterimFonk(){
	/*  Bezier e�risindeki �rnek kontrol noktas� say�s�n� ve �izdirilecek e�ri konumlar�n�n�n say�s�n� ayarla. */
	GLint kontrolNoktasiSayisi = 4, BezierEgrisiNoktaSayisi = 1000;
	wcPt3d kontrolNoktalari[4] = { { -40.0, -40.0, 0.0 },  { -80.0, -200.0, 0.0 }, { 80.0, -200.0, 0.0 },{40.0, 40.0, 0.0} };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Bezier e�risini �iz. */
	glPointSize(4);
	glColor3f(0.0, 1.0, 0.0);
	bezier(kontrolNoktasiSayisi, kontrolNoktalari, BezierEgrisiNoktaSayisi);

	/* Kontrol noktalar�n� �iz. */
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(12);
	for (int k = 0; k <= kontrolNoktasiSayisi; k++){
		noktaCiz(kontrolNoktalari[k]);
	}
	glFlush();
}

void pencereYenidenSekillendir(int yeniEn, int yeniBoy){
	glViewport(0, 0, yeniBoy, yeniBoy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100, 100, -250, 250);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	glutInit(&argc, (char**)argv);  // GLUT'u ba�lat
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB ); //g�sterim modunu ayarla
	glutInitWindowPosition(50, 50); // Pencerenin sol �st ekran k��esinden uzakl���n� ayarla
	glutInitWindowSize(pencereEni, pencereBoyu);   // Pencere boyunu ayarla
	glutCreateWindow("Bezier Egrisi");	// Verilen ba�l�kla pencereyi olu�tur
	init();							//�lklendirmeyi �al��t�r
	glutDisplayFunc(gosterimFonk); // Yeniden pencere �izimleri i�in g�sterim geri bildirim fonksiyonunu kay�tla
	glutReshapeFunc(pencereYenidenSekillendir);

	glutMainLoop();           // Sonsuz bir �ekilde s�re� i�lem d�ng�s�ne gir

	return 0;
}
