#include <GL/glut.h>

// Variabel untuk rotasi meja
float tableRotationAngle = 0.0f;
float scaleFactor = 1.0f; // Faktor skala untuk meja
float translationX = 0.0f, translationY = -1.0f, translationZ = 0.0f; // Variabel translasi untuk meja

// Fungsi untuk menggambar meja lengkap (alas + kaki meja)
void drawTable() {
    glPushMatrix();
    
    // Terapkan translasi untuk memindahkan meja
    glTranslatef(translationX, translationY, translationZ); // Translasi meja
    
    // Rotasi meja
    glRotatef(tableRotationAngle, 0.0f, 1.0f, 0.0f); // Rotasi meja pada sumbu Y

    // Menambahkan skala pada meja
    glScalef(scaleFactor, scaleFactor, scaleFactor); // Skala objek meja secara keseluruhan

    // Material untuk meja agar bisa menerima pencahayaan
    GLfloat mat_ambient[] = {0.4f, 0.2f, 0.0f, 1.0f}; // Warna ambient coklat kayu
    GLfloat mat_diffuse[] = {0.6f, 0.3f, 0.0f, 1.0f}; // Warna difus coklat kayu
    GLfloat mat_specular[] = {0.2f, 0.2f, 0.2f, 1.0f}; // Efek reflektif (specular)
    GLfloat mat_shininess[] = {30.0f}; // Kekasaran permukaan untuk refleksi

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Gambar alas meja sebagai kubus besar untuk ketebalan
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Posisikan alas meja di atas
    glScalef(4.0f, 0.2f, 4.0f); // Membuat alas meja lebih besar dan tebal
    glutSolidCube(1.0f); // Gambar alas meja sebagai kubus
    glPopMatrix();

    // Gambar kaki meja (menggunakan kubus kecil)
    glPushMatrix();
    // Kaki kiri depan
    glTranslatef(-1.8f, -2.0f, -1.8f); 
    glScalef(0.1f, 2.5f, 0.1f); 
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    // Kaki kanan depan
    glTranslatef( 1.8f, -2.0f, -1.8f); 
    glScalef(0.1f,  2.5f, 0.1f); 
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    // Kaki kiri belakang
    glTranslatef(-1.8f, -2.0f,  1.8f); 
    glScalef(0.1f,  2.5f, 0.1f); 
    glutSolidCube(2.0);
    glPopMatrix();

    glPushMatrix();
    // Kaki kanan belakang
    glTranslatef( 1.8f, -2.0f,  1.8f); 
    glScalef(0.1f,  2.5f, 0.1f); 
    glutSolidCube(2.0);
    glPopMatrix();

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // Mengatur kamera tanpa rotasi (menghadap ke posisi tetap)
    gluLookAt(10.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Kamera tetap pada posisi tetap

    // Gambar meja lengkap
    drawTable();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi keyboard untuk mengubah rotasi, skala, dan translasi
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'r': // Rotasi meja
            tableRotationAngle += 5.0f;
            if (tableRotationAngle > 360.0f) tableRotationAngle -= 360.0f;
            break;
        case '+': // Meningkatkan skala
            scaleFactor += 0.1f;
            break;
        case '-': // Mengurangi skala
            if (scaleFactor > 0.1f) scaleFactor -= 0.1f; // Mencegah skala menjadi terlalu kecil
            break;
        case 'w': // Translasi meja ke atas
            translationY += 0.1f;
            break;
        case 's': // Translasi meja ke bawah
            translationY -= 0.1f;
            break;
        case 'a': // Translasi meja ke kiri
            translationX -= 0.1f;
            break;
        case 'd': // Translasi meja ke kanan
            translationX += 0.1f;
            break;
        case 'q': // Translasi meja ke depan
            translationZ -= 0.1f;
            break;
        case 'e': // Translasi meja ke belakang
            translationZ += 0.1f;
            break;
        case 27: // Tombol ESC untuk keluar
            exit(0);
    }
    glutPostRedisplay(); // Meminta GLUT untuk merender ulang setelah perubahan
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Meja 3D");

    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); // Menambahkan callback untuk input keyboard
    glutMainLoop();
    return 0;
}

